#include <fstream>
#include <limits>
#include "Dictionary.h"

//ERRORS
const std::string INV_COM = "<INVALID_COMMAND>";
const std::string ALR_CRTD = "<DICTIONARY_ALREADY_CREATED>";
const std::string INV_FILE = "<INVALID_FILE>";
const std::string READF_ERR = "<READ_FILE_ERROR>";
const std::string INV_WORD = "<INVALID_WORD>";

using namespace sokolov;

int main()
{
  std::system("chcp 1251 > nul"); // > nul - text is not displayed
  setlocale(LC_ALL, "");

  Dictionary dictionary;
  int choice = -1;

  while (!std::cin.eof())
  {
    std::cout << "1 - Создать словарь на основе файла." << std::endl;
    std::cout << "2 - Добавить слово/слова в словарь." << std::endl;
    std::cout << "3 - Вывод словаря на консоль." << std::endl;
    std::cout << "4 - Вывести три чаще всего встречающихся слова." << std::endl;
    std::cout << "5 - Удалить слово из словаря." << std::endl;
    std::cout << "6 - Найти слово." << std::endl;
    std::cout << "(ctrl + Z) - Завершение программы." << std::endl;
    std::cout << "Выберите действие: ";
    std::cin >> choice;

    if (std::cin.eof())
    {
      choice = 0;
    }

    try
    {
      switch (choice)
      {

      case(0):
      {
        std::cout << "До свидания!\n";
        break;
      }

      case(1):
      {
        static int flag = 0; //checking the second dictionary creation
        flag++;
        if (flag > 1)
        {
          throw ALR_CRTD;
        }

        std::cout << "Введите имя файла: ";
        std::string filename;
        std::cin >> filename;
        std::ifstream file(filename);
        if (!file.is_open()) //reading a file and checking it
        {
          throw INV_FILE;
          break;
        }

        std::string line = "";
        while (std::getline(file, line)) //reading lines from a file
        {
          if (!readAddLine(dictionary, line)) //checking for readability
          {
            throw READF_ERR;
            break;
          }
        }
        std::cout << "Словарь создан.\n\n";
        file.close();
        break;
      }

      case(2):
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//clear std::cin before read

        std::cout << "Введите слово для добавления: ";
        std::string word = "";
        std::getline(std::cin, word);

        if (!dictionary.add(word, 1))
        {
          throw INV_WORD;
        }
        else
        {
          std::cout << "Слово добавлено.\n\n";
        }
        break;
      }

      case(3):
      {
        dictionary.print();
        break;
      }

      case(4):
      {
        std::vector<std::pair<std::string, int>> top3(3);
        findTop3(dictionary, top3);
        for (auto& i : top3)
        {
          std::cout << i.first << " - " << i.second << "\n";
        }
        std::cout << std::endl;
        break;
      }

      case(5):
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear std::cin before read

        std::cout << "Введите слово для удаления: ";
        std::string word = "";
        std::getline(std::cin, word);

        if (!dictionary.deleteWord(word))
        {
          throw INV_WORD;
        }
        else
        {
          std::cout << "Слово удалено.\n\n";
        }
        break;
      }

      case(6):
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear std::cin before read

        std::cout << "Введите слово для поиска: ";
        std::string word = "";
        std::getline(std::cin, word);

        auto it = dictionary.search(word);
        if (it != dictionary.getcend())
        {
          std::cout << "Слово найдено: " << it->first << " - " << it->second << "\n\n";
        }
        else
        {
          throw INV_WORD;
        }
        break;
      }

      default:
      {
        throw INV_COM;
        break;
      }
      }
    }
    catch (const std::string& err)
    {
      std::cerr << err << "\n";
    }
  }

  return 0;
}
