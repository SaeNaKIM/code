#include <boost/unordered_map.hpp>
#include <iostream>
#include <cassert>

using namespace std;
using namespace boost;

int main(int argc, char const* argv[])
{
  typedef unordered_map<string, int> map;

  map x;

  x["one"] = 1;
  x["two"] = 2;
  x["three"] = 3;

  assert(x.at("one") == 1);
  assert(x.at("two") == 2);
  assert(x.find("missing") == x.end());

  auto xend = x.end();
  for (auto it=x.begin(); it != xend; ++it)
   cout << it->first << " : " << it->second << endl;

  return 0;
}