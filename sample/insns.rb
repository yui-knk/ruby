class RubyVM::Insn
  def pop_num
    ret_num - stack_increase
  end
end

class RubyDecompiler
  class Self
    def to_ruby
      "self"
    end
  end

  class Constant
    def initialize(sym)
      @sym = sym
    end

    def to_ruby
      @sym.to_s
    end
  end

  class MethodCall
    def initialize(receiver:, args:, mid:, flags:)
      @receiver = receiver
      @args = args
      @mid = mid
      @flags = flags
    end

    def to_ruby
      if @flags[:FCALL]
        "#{@mid}(#{args_to_ruby})"
      else
        "#{receiver_to_ruby}.#{@mid}(#{args_to_ruby})"
      end
    end

    private

    def receiver_to_ruby
      case
      when @receiver.respond_to?(:to_ruby)
        @receiver.to_ruby
      else
        @receiver.inspect
      end
    end

    def args_to_ruby
      @args.map do |arg|
        case
        when arg.respond_to?(:to_ruby)
          arg.to_ruby
        else
          arg.inspect
        end
      end.join(", ")
    end
  end

  def initialize(iseq, line_sep = "\n")
    @iseq = iseq
    @line_sep = line_sep

    @parsed_iseq = false
    @generated_ruby_code = nil

    @vm_stack = []
    @method_calls = []
  end

  def decompile
    parse_iseq
    generate_ruby_code
  end

  private

  def parse_iseq
    @parsed_iseq ||= begin
      parse_insns

      true
    end
  end

  def parse_insns
    insns.each do |insn|
      case insn.name
      when "pop"
        popped = @vm_stack.pop

        if popped.is_a?(MethodCall)
          @method_calls.push popped
        end
      when "getconstant"
        @vm_stack.push Constant.new(insn.operands[0])
      when "putself"
        @vm_stack.push Self.new
      when "putobject"
        @vm_stack.push insn.operands[0]
      when "opt_send_without_block"
        mid = insn.operands[0][:mid]
        args = @vm_stack.pop insn.operands[0][:argc]
        receiver = @vm_stack.pop
        flags = insn.operands[0][:flags]

        mc = MethodCall.new(receiver: receiver, args: args, mid: mid, flags: flags)
        @vm_stack.push mc
      when "leave"
        @vm_stack.reverse.each do |elem|
          if elem.is_a?(MethodCall)
            @method_calls.push elem
          end
        end
      else
        # noop
      end
    end
  end

  def generate_ruby_code
    @generated_ruby_code ||= begin
      str = ""

      @method_calls.each do |mc|
        str << mc.to_ruby << @line_sep
      end

      str
    end
  end

  def local_variables
    @iseq.local_variables
  end

  def insns
    @iseq.insns
  end
end

# iseq = ::RubyVM::InstructionSequence.compile("p 10") # OK self.p(10)
# iseq = ::RubyVM::InstructionSequence.compile("p 10, 11") # OK self.p(10, 11)
# iseq = ::RubyVM::InstructionSequence.compile("p 11; p 10") # OK p(11); p(10);
# iseq = ::RubyVM::InstructionSequence.compile("p p 10") # OK self.p(self.p(10));
iseq = ::RubyVM::InstructionSequence.compile("p Object.new") # OK p(Object.new());
# iseq = ::RubyVM::InstructionSequence.compile("a = 10; b = a + 2")
insns = iseq.insns


if ENV["DEBUG_DECOMPILE"]
  puts iseq.disasm
  p iseq.local_variables

  insns.each do |i|
    p [i.name, i.types, i.len, i.operands, i.ret_num, i.pop_num, i.stack_increase]
  end

  puts ""
  puts "==================="
  puts ""
end

puts RubyDecompiler.new(iseq, "; ").decompile
