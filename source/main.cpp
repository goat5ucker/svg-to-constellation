#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <filesystem>
#include <fstream>

#include <tinyxml2.h>
#include "utils.hpp"
#include "converter.hpp"




int main()
{
    setlocale(LC_ALL, "");
    // директория, из которой будут читаться файлики:
    std::cout << "chosen working directory: " << dirs::in_path << std::endl;

    // задаю вектор со списком файлов:
    std::vector<std::string> filelist;
    for (const auto & entry : std::filesystem::directory_iterator(dirs::in_path))
    {
        filelist.push_back(entry.path().string());
    }

    std::cout << "here's three (or less) files i saw there: ";
    for (int i = 0; i < std::min(3,(int)filelist.size()); i++)
    {
        std::cout << "\n    \' " << filelist[i] << " \'";
    }
    std::cout<< ";\n";

    std::cout << "ready to convert files one-by-one from " << dirs::in_path << " into .constellation.txt; ";

    for (int i = 0; i < filelist.size(); i++)
    {
        std::cout << " press enter..." << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "passing " << filelist [i] << " to the converter..." << std::endl;
        converter::main(filelist[i]);
    }

    std::cout << "converter is exiting with code 1: successful..." << std::endl;

    return 1;
}