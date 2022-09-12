class TestAstBrokenScript < Test::Unit::TestCase
  def test_defn_bodystmt_is_broken_1
    node = RubyVM::AbstractSyntaxTree.parse(<<~STR, suppress_syntax_error: true)
      class A
        def m1
          1 +
        end
      end
    STR

    # pp node
  end

  def test_defn_bodystmt_is_broken_2
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

  def test_defn_bodystmt_is_broken_3
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

  def test_defn_bodystmt_is_broken_4
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
end
