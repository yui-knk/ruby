class A
  def foo
  end
end

begin
  A.new.foo.bar
# rescue => e
#   p e.backtrace_locations.map(&:object_id)
#   p e.backtrace_locations.map(&:node_id)

#   raise
end
