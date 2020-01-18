#pragma once

#include <vector>
#include <tuple>

extern void parsing(const std::string &fPath,
    std::vector<std::tuple<std::string,
    int, std::vector<std::string>>> &tasks);
extern void scheduling(std::vector<std::tuple<std::string,
    int, std::vector<std::string>>> &tasks);
