#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <exception>
#include <vector>
#include <iostream>

using namespace std;
using boost::property_tree::ptree;

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void print_all(ptree& pt)
{
}

//
// 1. "array.dict" type
//
void print_selected(ptree& pt, string const& key, vector<int> const& selection)
{
    using namespace boost;
    
    ptree::iterator pbeg = pt.get_child(key).begin();
    ptree::iterator pend = pt.get_child(key).end();

    while (pbeg != pend)
    {
        ptree t; t.push_back(std::make_pair("dict", pbeg->second));

        ptree& tree = t.get_child("dict");
        ptree::iterator beg = tree.begin();
        ptree::iterator end = tree.end();
        int index = 0;
        while (beg != end)
        {
            if (find(selection.begin(), selection.end(), index) != selection.end())
            {
                string key   = beg->second.data(); beg++;
                string value = beg->second.data(); beg++;

                cout << "key   : " << key   << endl
                     << "value : " << value << endl << endl;
            }
            else
            {
                std::advance(beg, 2);
            }
            index++;
        }

        ++pbeg;
    }
}

int main()
{
    try
    {
        ptree pt;
        read_xml("history.xml", pt);

        vector<int> sel;
        sel.push_back(0);
        sel.push_back(1);
        sel.push_back(2);

        string key = "plist.dict.array";
        print_selected(pt, key, sel);

    }
    catch (std::exception &e)
    {
        std::cout << "error: " << e.what() << "\n";
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
