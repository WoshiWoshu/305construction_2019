#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <vector>
#include <iterator>
#include <tuple>
#include "Utility.hpp"

static void errorHandleParsing(const std::string &data, const int &count)
{
    if ((count == 0 || count == 1 || count >= 3) && isPosNum(data))
        exit(84);
    if (count == 2 && !isPosNum(data))
        exit(84);
}

void parsing(const std::string &fPath,
    std::vector<std::tuple<std::string,
    int, std::vector<std::string>>> &tasks)
{
    std::ifstream read;
    std::pair<std::string, std::stringstream> fContent;
    std::tuple<std::string, int, std::vector<std::string>> listTmp;
    int count(0);

    read.open(fPath.c_str());
    if (!read) {
        std::cerr << "[ERROR] : File could not be opened" << std::endl;
        exit(84);
    }
    while (std::getline(read, fContent.first)) {
        fContent.second.clear();
        fContent.second.str(fContent.first);
        while (std::getline(fContent.second, fContent.first, ';')) {
            errorHandleParsing(fContent.first, count);
            fContent.first.erase(remove_if(fContent.first.begin(), fContent.first.end(), isspace), fContent.first.end());
            std::get<0>(listTmp) = count == 0 ? fContent.first : std::get<0>(listTmp);
            std::get<1>(listTmp) = count == 2 ?  std::stoi(fContent.first) : std::get<1>(listTmp);
            count >= 3 ?
            std::get<2>(listTmp).push_back(fContent.first) : void();
            count++;
        }
        if (count <= 2)
            exit (84);
        tasks.push_back(listTmp);
        std::get<2>(listTmp).clear();
        count = 0;
    }
    read.close();
}
