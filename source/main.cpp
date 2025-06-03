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
    // директория, из которой будут читаться файлики:
    std::cout << "выбранная рабочая директория: " << dirs::in_path << std::endl;

    // задаю вектор со списком файлов:
    std::vector<std::string> filelist;
    for (const auto & entry : std::filesystem::directory_iterator(dirs::in_path))
    {
        filelist.push_back(entry.path().string());
    }

    std::cout << "увидел первые 3 (или меньше) файла оттуда: ";
    for (int i = 0; i < std::min(3,(int)filelist.size()); i++)
    {
        std::cout << "\n    \' " << filelist[i] << " \'";
    }
    std::cout<< ";\n";

    std::cout << "готов конвертировать файлы по одному из " << dirs::in_path << " в формат .const; ";

    for (int i = 0; i < filelist.size(); i++)
    {
        std::cout << " нажмите enter..." << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "передаю " << filelist [i] << " конвертеру..." << std::endl;
        converter::main(filelist[i]);
    }

    std::cout << "конвертер завершает работу..." << std::endl;

    return 1;
}