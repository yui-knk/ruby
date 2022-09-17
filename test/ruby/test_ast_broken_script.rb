class TestAstBrokenScript < Test::Unit::TestCase
  def test_if_1
    node = RubyVM::AbstractSyntaxTree.parse(<<~STR, suppress_syntax_error: true)
      class A
        def m
          a = 10
          if # here
        end
      end
    STR

    pp node
  end

  def test_method_call_1
    node = RubyVM::AbstractSyntaxTree.parse(<<~STR, suppress_syntax_error: true)
      module Z
        class Foo
          foo.
        end
      
        def bar
        end
      end
    STR

    pp node
  end

  def test_defn_bodystmt_is_1
    node = RubyVM::AbstractSyntaxTree.parse(<<~STR, suppress_syntax_error: true)
      class A
        def m1
          1 +
        end
      end
    STR

    # pp node
  end

  def test_defn_bodystmt_is_2
    node = RubyVM::AbstractSyntaxTree.parse(<<~STR, suppress_syntax_error: true)
      class A
        def m1
          v = 10
          1 +
        end
      end
    STR

    # pp node
  end

  def test_defn_bodystmt_is_3
    node = RubyVM::AbstractSyntaxTree.parse(<<~STR, suppress_syntax_error: true)
      class A
        def m1
          1 +
        end

        def m2
          v = 10
          1 +
        end
      end
    STR

    # pp node
  end

  def test_defn_bodystmt_is_4
    node = RubyVM::AbstractSyntaxTree.parse(<<~STR, suppress_syntax_error: true)
      class A
        def m1
          v = 1

          if v > 0
            a.b
        end
      end
    STR

    # pp node
  end

  def test_nested_do_end_1
    node = RubyVM::AbstractSyntaxTree.parse(<<~STR, suppress_syntax_error: true)
    describe "1" do
      describe "2" do
        describe "3" do
          it "here" do
        end
      end
    end
    STR

    # pp node
  end

  def test_braces_1
    node = RubyVM::AbstractSyntaxTree.parse(<<~STR, suppress_syntax_error: true)
    class A
      def m1
        a = 1
        10.times {
        b = 2
      end

      def m2
        c = 3
        11.times {
        d = 4
      end
    end
    STR

    # pp node
  end



  # def test_string_interpolation_1
  #   node = RubyVM::AbstractSyntaxTree.parse(<<~'STR', suppress_syntax_error: true)
  #   a = 1
  #   str = "#{a}_#{"
  #   b = 2
  #   STR

  #   pp node
  # end
end
