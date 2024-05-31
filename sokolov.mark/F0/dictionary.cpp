#include "Dictionary.h"

bool sokolov::isOKstring(std::string& str)
{
  return str.find_first_of("0123456789.,/?\'\"-_+=:;)(&^%$#@!~`*<>{}][|\\") == std::string::npos;;
}

void sokolov::toLowerStr(std::string& str)
{
  std::transform(str.begin(), str.end(), str.begin(), ::tolower); //
}

bool sokolov::readAddLine(Dictionary& dict, std::string& line)
{
  std::istringstream iss(line);
  std::string key = "";

  bool flag = false;
  while (std::getline(iss, key, ' '))
  {
    if (dict.add(key, 1))
    {
      flag = true;
    }
  }
  if (flag)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void sokolov::findTop3(Dictionary& dict, std::vector<std::pair<std::string, int>>& top3)
{
  for (auto& i : dict.dictionary_)
  {
    for (int j = 0; j < top3.size(); j++)
    {
      if (i.second > top3[j].second)
      {
        if (j == 0)
        {
          top3[2] = top3[1];
          top3[1] = top3[0];
        }
        if (j == 1)
        {
          top3[2] = top3[1];
        }
        top3[j] = { i.first, i.second };
        break;
      }
    }
  }
}

bool sokolov::Dictionary::add(std::string& key, int count)
{
  toLowerStr(key);
  if (!sokolov::isOKstring(key) || key == "")
  {
    return false;
  }

  auto it = dictionary_.find(key);
  if (it != dictionary_.cend())
  {
    it->second++;
  }
  else
  {
    dictionary_.insert({ key, count });
  }
  return true;
}

bool sokolov::Dictionary::deleteWord(std::string& key)
{
  sokolov::toLowerStr(key);
  return dictionary_.erase(key) != 0; //
}

void sokolov::Dictionary::print() const
{
  std::cout << "Словарь:\n";
  for (auto& i : dictionary_)
  {
    std::cout << i.first << " - " << i.second << "\n";
  }
  std::cout << std::endl;
}

sokolov::Dictionary::const_iterator sokolov::Dictionary::search(std::string& key) const
{
  sokolov::toLowerStr(key);
  return dictionary_.find(key);
}

sokolov::Dictionary::const_iterator sokolov::Dictionary::getcbegin() const
{
  return dictionary_.cbegin();
}

sokolov::Dictionary::const_iterator sokolov::Dictionary::getcend() const
{
  return dictionary_.cend();
}
