module Lrama
  class Grammar
    class Code
      class AfterShiftCode < Code
        private

        # * ($$) error
        # * (@$) error
        # * ($:$) error
        # * ($1) error
        # * (@1) error
        # * ($:1) error
        def reference_to_c(ref)
          case
          when ref.type == :dollar && ref.name == "$" # $$
            raise "$#{ref.value} can not be used in after_shift."
          when ref.type == :at && ref.name == "$" # @$
            raise "@#{ref.value} can not be used in after_shift."
          when ref.type == :index && ref.name == "$" # $:$
            raise "$:#{ref.value} can not be used in after_shift."
          when ref.type == :dollar # $n
            raise "$#{ref.value} can not be used in after_shift."
          when ref.type == :at # @n
            raise "@#{ref.value} can not be used in after_shift."
          when ref.type == :index # $:n
            raise "$:#{ref.value} can not be used in after_shift."
          else
            raise "Unexpected. #{self}, #{ref}"
          end
        end
      end
    end
  end
end
