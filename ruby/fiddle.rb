#!/usr/bin/env ruby

require "fiddle"

libm = Fiddle.dlopen('/usr/lib/libm.dylib')

function = Fiddle::Function.new(libm['sin'],
  [Fiddle::TYPE_DOUBLE], Fiddle::TYPE_DOUBLE
)

puts function.call(90 * Math::PI / 180)
