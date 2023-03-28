require_relative 'assert_parse_files.rb'
class TestRipper::Generic
  Dir["#{SRCDIR}/test/pattern_matching/"].each do |dir|
    dir = dir[(SRCDIR.length+1)..-2]
    define_method("test_parse_files:#{dir}") do
      100.times do
        assert_parse_files(dir)
      end
    end
  end
end
