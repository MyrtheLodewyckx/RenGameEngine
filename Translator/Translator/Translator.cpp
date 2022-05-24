#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <ostream>
#include <windows.h>

std::string ReadFile(const std::string& filename);
std::string Convert437ToUTF8(const std::string& text);


int main()
{
    auto in = ReadFile("code page 437.txt");
    auto utf8Result = Convert437ToUTF8(in);
    std::ofstream("utf8result.txt") << utf8Result;

    in = ReadFile("test.txt");
    auto TestResult = Convert437ToUTF8(in);
    std::ofstream("testResult.txt") << TestResult;

   auto result = ReadFile("utf-8.txt");

    const int nr = MultiByteToWideChar(CP_UTF8, 0, result.c_str(), (int)result.size(), NULL, NULL);
    std::wstring wOut(nr, 0);
    MultiByteToWideChar(CP_UTF8, 0, result.c_str(), (int)result.length(), &wOut[0], nr);


    int count = WideCharToMultiByte(437, 0, wOut.c_str(), (int)wOut.length(), NULL, 0, NULL, NULL);
    std::string out(count, 0);
    WideCharToMultiByte(437, WC_NO_BEST_FIT_CHARS | WC_COMPOSITECHECK | WC_DEFAULTCHAR, wOut.c_str(), 0, &out[0], count, (LPCCH)'9', NULL);

    std::ofstream("437result.txt") << out;
}
                                                  

std::string ReadFile(const std::string& filename)
{
    std::ifstream file{ filename, std::ios::in | std::ios::binary };
    std::string text;


    if (file.is_open())
    {
        while (!file.eof())
        {
            std::string str;
            std::getline(file, str);
            text += str;
        }
    }
    else
        std::cout << "file won't open.";

    file.close();

    return text;
}

std::string Convert437ToUTF8(const std::string& text)
{
    const int nr = MultiByteToWideChar(437, MB_PRECOMPOSED, text.c_str(), (int)text.size(), NULL, NULL);
    std::wstring wOut(nr, 0);
    MultiByteToWideChar(437, MB_PRECOMPOSED, text.c_str(), (int)text.length(), &wOut[0], nr);


    int count = WideCharToMultiByte(CP_UTF8, 0, wOut.c_str(), (int)wOut.length(), NULL, 0, NULL, NULL);
    std::string out(count, 0);
    WideCharToMultiByte(CP_UTF8, 0, wOut.c_str(), -1, &out[0], count, (LPCCH)'9', NULL);

    return out;
}
