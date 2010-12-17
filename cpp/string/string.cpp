#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

template<typename T>
T from_string(string const& s)
{
  istringstream is(s);
  T t; is >> t;
  return t;
}

template<typename T>
string to_string(T const& t)
{
  ostringstream s;
  s << t;

  return s.str();
}

void split(const string& line, const string& separators, vector<string>& tokens) 
{   
  size_t start = line.find_first_not_of(separators);
  size_t end   = line.length();

  while ((start >=0) && (start < end))
  {
    size_t stop = line.find_first_of(separators, start);
    if ((stop < 0) || (stop > end)) stop = end;
    tokens.push_back(line.substr(start, stop-start));
    start = line.find_first_not_of(separators, stop+1);
  }   
}

int main(int argc, char const* argv[])
{
  ifstream f("test.txt");
  string line;
  while (getline(f, line))
  {
    vector<string> strs;
    split(line, " ", strs);
    double n = from_string<double>(strs[2]);
    cout << n << endl;
  }

  return 0;
}