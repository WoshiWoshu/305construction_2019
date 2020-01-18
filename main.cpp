#include <string>
#include <iostream>
#include <cstring>
#include "Construction.hpp"

static void displayHelp(void)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./305construction file" << std::endl << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tfile\tfile describing the tasks" << std::endl;
}

static void construction(const std::string &fPath)
{
    std::vector<std::tuple<std::string, int,
    std::vector<std::string>>> tasks;

    parsing(fPath, tasks);
    scheduling(tasks);
}

int main(int ac, char **av)
{
    if (ac == 2 and strcmp(av[1], "-h") == 0)
        displayHelp();
    else if (ac == 2)
        construction(av[1]);
    else
        return 84;
    return 0;
}
