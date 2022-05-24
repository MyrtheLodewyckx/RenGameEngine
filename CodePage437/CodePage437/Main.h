#pragma once
#include <stringapiset.h>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int main()
{

    std::ifstream file{ "code page 437.txt", std::ios::in | std::ios::binary };

    std::string text;

    if (file.is_open())
    {
        while (!file.eof())
        {
            std::string str;
            std::getline(file, str);
            text = text + str;
        }
    }
    else
        std::cout << "file won't open.";

	auto out  = MultiByteToWideChar(437, MB_PRECOMPOSED,text.c_str(),text.size(),NULL,NULL);
    std::cout << out;

}