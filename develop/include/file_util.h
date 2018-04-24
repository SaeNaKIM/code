#include <istream>
#include <cstdint>

namespace util::file {
////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
bool exists(std::string const& path);
auto exists(char const* path) -> bool;

auto size(const char* filename) -> long;
auto size(std::ifstream& in) -> long;

auto read(std::istream& in, long offset, int size) -> std::uint8_t*;
  
auto read_uint4_be(std::istream& in, long offset) -> std::uint32_t;
////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
}
