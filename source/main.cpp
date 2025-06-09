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
    // промпт если прога не обнаружит рабочей директории;
    while(!std::filesystem::exists(dirs::in_path))
    {
        std::cout << "it seems like folder structure is non-existent, would you like me to create them?" << std::endl;
        std::cout << "enter 1 for proceending, or any other number for exiting the program..." << std::endl;
        int x = -1;
    enter_val:
        std::cin >> x;
        if(std::cin.fail())
        {
            std::cin.clear(); std::cin.ignore(32768, '\n');
            std::cout << "uh oh, please enter a valid value: 1 for proceeding, or any other for exiting" << std::endl;
            goto enter_val;
        }
        std::cin.clear(); std::cin.ignore(32768, '\n');
        if(x==1)
        {
            std::filesystem::create_directories(dirs::in_path);
        }
        else return 1;

        std::cout << "here's your working dir path: " << std::filesystem::absolute(dirs::in_path) << std::endl;
        std::cout << "place some files in there and press enter here:";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

    std::cout << std::fixed << "working directory: " << dirs::in_path << std::endl;

    // задаю вектор со списком файлов:
    std::vector<std::string> filelist;

    // считываю файлы оттуда:
    for (const auto & entry : std::filesystem::directory_iterator(dirs::in_path))
    {
        filelist.push_back(entry.path().string());
    }
    if(filelist.size() == 0)
    {
        std::cout << "it seems like there's no files in " << std::filesystem::absolute(dirs::in_path) << std::endl;
        std::cout << "you can place some files there and enter 1 here to proceed.\n    or enter any other number to exit right away." << std::endl;
        int x = -1;
    fileprompt:
        std::cin >> x;
        if(std::cin.fail())
        {
            std::cin.clear(); std::cin.ignore(32768, '\n');
            std::cout << "enter 1 if you've put files in working dir, " << dirs::in_path << std::endl;
            std::cout << "    or enter any other number to exit right away." << std::endl;
            goto fileprompt;
        }
        std::cin.clear(); std::cin.ignore(32768, '\n');
    }

    std::cout << "here's three (or less) files i saw there: ";
    for (int i = 0; i < (int)filelist.size(); i++)
    {
        std::cout << "\n    \' " << filelist[i] << " \'" << std::endl;
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

    std::cout << "files have been converted; press enter to exit:";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); std::cout << std::endl;

    std::cout << "converter is exiting with code 1: successful..." << std::endl;

    return 1;


}