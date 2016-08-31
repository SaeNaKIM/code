#!/usr/bin/env ruby

require "set"

set = Set.new
str = "a very very long string"

str.scan(/\w+/).each { |word| 
  p word unless set.add?(word)
}

