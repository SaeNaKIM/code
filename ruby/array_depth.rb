#!/usr/bin/env ruby2.0 -wKU
# encoding: utf-8

class Object
  def depth
    0
  end
end

class Array
  def depth
    first.depth + 1
  end
end

puts [].depth
puts [[]].depth
puts [[[]]].depth
