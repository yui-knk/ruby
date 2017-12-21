# frozen_string_literal: false
require 'test/unit'
require "-test-/ast"

class AST
  class Location
    include Comparable
    attr_reader :lineno, :column
    def initialize(lineno, column)
      @lineno = lineno
      @column = column
    end

    def <=>(other)
      case
      when lineno < other.lineno
        -1
      when lineno == other.lineno
        column <=> other.column
      when lineno > other.lineno
        1
      end
    end
  end

  def first_loc
    [first_lineno, first_column]
  end

  def last_loc
    [last_lineno, last_column]
  end

  def first_loc_1
    Location.new(first_lineno, first_column)
  end

  def last_loc_1
    Location.new(last_lineno, last_column)
  end

  alias to_s inspect
end

class TestAst < Test::Unit::TestCase
  class Helper
    def self.build_from_file(path)
      new(File.read(path))
    end

    attr_reader :errors

    def initialize(str)
      @str = str
      @errors = []
      @debug = false
    end

    def validate_range
      @errors = []
      validate_range0(ast)

      @errors.empty?
    end

    def validate_not_cared
      @errors = []
      validate_not_cared0(ast)

      @errors.empty?
    end

    def ast
      return @ast if defined?(@ast)
      ast = AST.parse(@str)
      raise "Syntax error: #{@str}" if ast.nil?
      @ast = ast
    end

    private

    def validate_range0(node)
      first_loc, last_loc = node.first_loc, node.last_loc
      children = node.children.compact

      return true if children.empty?
      # These NODE_D* has NODE_ARRAY as nd_next->nd_next whose last locations
      # we can not update when item is appended.
      return true if ["NODE_DSTR", "NODE_DXSTR", "NODE_DREGX", "NODE_DSYM"].include? node.type

      min = children.map(&:first_loc).min
      max = children.map(&:last_loc).max

      unless [min, first_loc].min == first_loc
        @errors << { type: :min_validation_error, min: min, first_loc: first_loc, node: node }
      end

      unless [max, last_loc].max == last_loc
        @errors << { type: :max_validation_error, max: max, last_loc: last_loc, node: node }
      end

      p "#{node} => #{children}" if @debug

      children.each do |child|
        p child if @debug
        validate_range0(child)
      end
    end

    def validate_not_cared0(node)
      first_loc, last_loc = node.first_loc, node.last_loc
      children = node.children.compact

      @errors << { type: :first_lineno, node: node } if first_loc[0] == 0
      @errors << { type: :first_column, node: node } if first_loc[1] == -1
      @errors << { type: :last_lineno,  node: node } if last_loc[0]  == 0
      @errors << { type: :last_column,  node: node } if last_loc[1]  == -1

      children.each {|c| validate_not_cared0(c) }
    end
  end

  SRCDIR = File.expand_path("../../../..", __FILE__)

  Dir.glob("#{SRCDIR}/test/**/*.rb").each do |path|
    define_method("test_ranges:#{path}") do
      helper = Helper.build_from_file(path)
      helper.validate_range

      assert_equal(0, helper.errors.count)
    end
  end

  Dir.glob("#{SRCDIR}/test/**/*.rb").each do |path|
    define_method("test_not_cared:#{path}") do
      helper = Helper.build_from_file(path)
      helper.validate_not_cared

      assert_equal(0, helper.errors.count)
    end
  end
end
