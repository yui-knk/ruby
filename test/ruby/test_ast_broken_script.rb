require "pp"

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

    str = ""
    PP.pp(node, str)
    assert_equal(<<~EXP, str)
      (SCOPE@1:0-6:3
       tbl: []
       args: nil
       body:
         (CLASS@1:0-6:3 (COLON2@1:6-1:7 nil :A) nil
            (SCOPE@1:0-6:3
             tbl: []
             args: nil
             body:
               (BLOCK@1:7-6:3 (BEGIN@1:7-1:7 nil)
                  (DEFN@2:2-6:3
                   mid: :m
                   body:
                     (SCOPE@2:2-6:3
                      tbl: [:a]
                      args:
                        (ARGS@2:7-2:7
                         pre_num: 0
                         pre_init: nil
                         opt: nil
                         first_post: nil
                         post_num: 0
                         post_init: nil
                         rest: nil
                         kw: nil
                         kwrest: nil
                         block: nil)
                      body:
                        (BLOCK@3:4-6:3 (LASGN@3:4-3:10 :a (LIT@3:8-3:10 10))
                           (IF@4:4-6:3 (ERROR@5:2-5:5) nil nil))))))))
    EXP
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

    str = ""
    PP.pp(node, str)
    assert_equal(<<~EXP, str)
      (SCOPE@1:0-8:3
       tbl: []
       args: nil
       body:
         (MODULE@1:0-8:3 (COLON2@1:7-1:8 nil :Z)
            (SCOPE@1:0-8:3
             tbl: []
             args: nil
             body:
               (BLOCK@1:8-7:5 (BEGIN@1:8-1:8 nil)
                  (CLASS@2:2-4:5 (COLON2@2:8-2:11 nil :Foo) nil
                     (SCOPE@2:2-4:5
                      tbl: []
                      args: nil
                      body:
                        (BLOCK@2:11-4:5 (BEGIN@2:11-2:11 nil)
                           (CALL@3:4-4:5 (VCALL@3:4-3:7 :foo) :"?"
                              (ERROR@4:2-4:5)))))
                  (DEFN@6:2-7:5
                   mid: :bar
                   body:
                     (SCOPE@6:2-7:5
                      tbl: []
                      args:
                        (ARGS@6:9-6:9
                         pre_num: 0
                         pre_init: nil
                         opt: nil
                         first_post: nil
                         post_num: 0
                         post_init: nil
                         rest: nil
                         kw: nil
                         kwrest: nil
                         block: nil)
                      body: nil))))))
    EXP
  end

  def test_defn_bodystmt_is_1
    node = RubyVM::AbstractSyntaxTree.parse(<<~STR, suppress_syntax_error: true)
      class A
        def m1
          1 +
        end
      end
    STR

    str = ""
    PP.pp(node, str)
    assert_equal(<<~EXP, str)
      (SCOPE@1:0-5:3
       tbl: []
       args: nil
       body:
         (CLASS@1:0-5:3 (COLON2@1:6-1:7 nil :A) nil
            (SCOPE@1:0-5:3
             tbl: []
             args: nil
             body:
               (BLOCK@1:7-4:5 (BEGIN@1:7-1:7 nil)
                  (DEFN@2:2-4:5
                   mid: :m1
                   body:
                     (SCOPE@2:2-4:5
                      tbl: []
                      args:
                        (ARGS@2:8-2:8
                         pre_num: 0
                         pre_init: nil
                         opt: nil
                         first_post: nil
                         post_num: 0
                         post_init: nil
                         rest: nil
                         kw: nil
                         kwrest: nil
                         block: nil)
                      body: (ERROR@3:4-4:5)))))))
    EXP
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

    str = ""
    PP.pp(node, str)
    assert_equal(<<~EXP, str)
      (SCOPE@1:0-6:3
       tbl: []
       args: nil
       body:
         (CLASS@1:0-6:3 (COLON2@1:6-1:7 nil :A) nil
            (SCOPE@1:0-6:3
             tbl: []
             args: nil
             body:
               (BLOCK@1:7-5:5 (BEGIN@1:7-1:7 nil)
                  (DEFN@2:2-5:5
                   mid: :m1
                   body:
                     (SCOPE@2:2-5:5
                      tbl: [:v]
                      args:
                        (ARGS@2:8-2:8
                         pre_num: 0
                         pre_init: nil
                         opt: nil
                         first_post: nil
                         post_num: 0
                         post_init: nil
                         rest: nil
                         kw: nil
                         kwrest: nil
                         block: nil)
                      body:
                        (BLOCK@3:4-5:5 (LASGN@3:4-3:10 :v (LIT@3:8-3:10 10))
                           (ERROR@4:4-5:5))))))))
    EXP
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

    str = ""
    PP.pp(node, str)
    assert_equal(<<~EXP, str)
      (SCOPE@1:0-10:3
       tbl: []
       args: nil
       body:
         (CLASS@1:0-10:3 (COLON2@1:6-1:7 nil :A) nil
            (SCOPE@1:0-10:3
             tbl: []
             args: nil
             body:
               (BLOCK@1:7-9:5 (BEGIN@1:7-1:7 nil)
                  (DEFN@2:2-4:5
                   mid: :m1
                   body:
                     (SCOPE@2:2-4:5
                      tbl: []
                      args:
                        (ARGS@2:8-2:8
                         pre_num: 0
                         pre_init: nil
                         opt: nil
                         first_post: nil
                         post_num: 0
                         post_init: nil
                         rest: nil
                         kw: nil
                         kwrest: nil
                         block: nil)
                      body: (ERROR@3:4-4:5)))
                  (DEFN@6:2-9:5
                   mid: :m2
                   body:
                     (SCOPE@6:2-9:5
                      tbl: [:v]
                      args:
                        (ARGS@6:8-6:8
                         pre_num: 0
                         pre_init: nil
                         opt: nil
                         first_post: nil
                         post_num: 0
                         post_init: nil
                         rest: nil
                         kw: nil
                         kwrest: nil
                         block: nil)
                      body:
                        (BLOCK@7:4-9:5 (LASGN@7:4-7:10 :v (LIT@7:8-7:10 10))
                           (ERROR@8:4-9:5))))))))
    EXP
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

    str = ""
    PP.pp(node, str)
    assert_equal(<<~EXP, str)
      (SCOPE@1:0-8:3
       tbl: []
       args: nil
       body:
         (CLASS@1:0-8:3 (COLON2@1:6-1:7 nil :A) nil
            (SCOPE@1:0-8:3
             tbl: []
             args: nil
             body:
               (BLOCK@1:7-8:3 (BEGIN@1:7-1:7 nil)
                  (DEFN@2:2-8:3
                   mid: :m1
                   body:
                     (SCOPE@2:2-8:3
                      tbl: [:v]
                      args:
                        (ARGS@2:8-2:8
                         pre_num: 0
                         pre_init: nil
                         opt: nil
                         first_post: nil
                         post_num: 0
                         post_init: nil
                         rest: nil
                         kw: nil
                         kwrest: nil
                         block: nil)
                      body:
                        (BLOCK@3:4-7:5 (LASGN@3:4-3:9 :v (LIT@3:8-3:9 1))
                           (IF@5:4-7:5
                              (OPCALL@5:7-5:12 (LVAR@5:7-5:8 :v) :>
                                 (LIST@5:11-5:12 (LIT@5:11-5:12 0) nil))
                              (CALL@6:6-6:9 (VCALL@6:6-6:7 :a) :b nil) nil))))))))
    EXP
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

    str = ""
    PP.pp(node, str)
    assert_equal(<<~EXP, str)
      (SCOPE@1:0-7:3
       tbl: []
       args: nil
       body:
         (ITER@1:0-7:3
            (FCALL@1:0-1:12 :describe (LIST@1:9-1:12 (STR@1:9-1:12 "1") nil))
            (SCOPE@1:13-7:3
             tbl: []
             args: nil
             body:
               (ITER@2:2-7:3
                  (FCALL@2:2-2:14 :describe (LIST@2:11-2:14 (STR@2:11-2:14 "2") nil))
                  (SCOPE@2:15-7:3
                   tbl: []
                   args: nil
                   body:
                     (ITER@3:4-6:5
                        (FCALL@3:4-3:16 :describe
                           (LIST@3:13-3:16 (STR@3:13-3:16 "3") nil))
                        (SCOPE@3:17-6:5
                         tbl: []
                         args: nil
                         body:
                           (ITER@4:6-5:7
                              (FCALL@4:6-4:15 :it
                                 (LIST@4:9-4:15 (STR@4:9-4:15 "here") nil))
                              (SCOPE@4:16-5:7
                               tbl: []
                               args: nil
                               body: (BEGIN@4:18-4:18 nil))))))))))
    EXP
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

    str = ""
    PP.pp(node, str)
    assert_equal(<<~EXP, str)
      (SCOPE@1:0-13:3
       tbl: []
       args: nil
       body:
         (CLASS@1:0-13:3 (COLON2@1:6-1:7 nil :A) nil
            (SCOPE@1:0-13:3
             tbl: []
             args: nil
             body:
               (BLOCK@1:7-12:5 (BEGIN@1:7-1:7 nil)
                  (DEFN@2:2-6:5
                   mid: :m1
                   body:
                     (SCOPE@2:2-6:5
                      tbl: [:a]
                      args:
                        (ARGS@2:8-2:8
                         pre_num: 0
                         pre_init: nil
                         opt: nil
                         first_post: nil
                         post_num: 0
                         post_init: nil
                         rest: nil
                         kw: nil
                         kwrest: nil
                         block: nil)
                      body:
                        (BLOCK@3:4-6:5 (LASGN@3:4-3:9 :a (LIT@3:8-3:9 1))
                           (ERROR@4:4-6:5))))
                  (DEFN@8:2-12:5
                   mid: :m2
                   body:
                     (SCOPE@8:2-12:5
                      tbl: [:c]
                      args:
                        (ARGS@8:8-8:8
                         pre_num: 0
                         pre_init: nil
                         opt: nil
                         first_post: nil
                         post_num: 0
                         post_init: nil
                         rest: nil
                         kw: nil
                         kwrest: nil
                         block: nil)
                      body:
                        (BLOCK@9:4-12:5 (LASGN@9:4-9:9 :c (LIT@9:8-9:9 3))
                           (ERROR@10:4-12:5))))))))
    EXP
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
