#ifndef DICTIONARY
#define DICTIONARY

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include <vector>

namespace sokolov
{

  class Dictionary
  {
    std::map<std::string, int> dictionary_;

    friend bool isOKstring(std::string& str);
    friend void toLowerStr(std::string& str);
    friend bool readAddLine(Dictionary& dict, std::string& line);
    friend void findTop3(Dictionary& dict, std::vector<std::pair<std::string, int>>& top3); //there must be a friend(becouse using private zone)

  public:
    using iterator = std::map<std::string, int>::iterator;
    using const_iterator = std::map<std::string, int>::const_iterator;

    Dictionary() = default;

    bool add(std::string& key, int count);
    bool deleteWord(std::string& key);
    void print() const;

    const_iterator search(std::string& key) const;
    const_iterator getcbegin() const;
    const_iterator getcend() const;
  };
}

#endif
