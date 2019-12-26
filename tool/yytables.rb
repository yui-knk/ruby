#!/usr/bin/env ruby

in_table_parsing = false

File.open(ARGV.first, "rb").each do |f|
  f.each_line do |l|
    l.chomp!

    if /\A#define (YYPACT_NINF|YYLAST)\s+\(?(-?\d+)\)?\z/ =~ l
      puts "#define #{$1}_NO_DEFAULT_REDUCTION #{$2}\n\n"
      next
    end

    if in_table_parsing
      puts l

      if l == "};"
        in_table_parsing = false
        puts "\n"
      end

      next
    end

    if /\Astatic const (.*) (yypact|yytable|yycheck)\[\] =\z/ =~ l
      in_table_parsing = true
      puts "static const #{$1} #{$2}_no_default_reduction[] ="
    end
  end
end
