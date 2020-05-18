#include "pch.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <string>
#include <locale>
#include <codecvt>
#include <fstream>

using namespace std;

string unicode2ansi(const std::wstring &wstr)
{
    int size_needed = WideCharToMultiByte(CP_ACP, 0, &wstr[0], -1, NULL, 0, NULL, NULL);
    string strTo(size_needed, 0);
    WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

wstring ansi2unicode(const std::string &str)
{
    int size_needed = MultiByteToWideChar(CP_ACP, 0, &str[0], (int)str.size(), NULL, 0);
    wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_ACP, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}
int main(int argc, char *argv[])
{
    locale loc(locale(), new codecvt_utf16<wchar_t>);
    string name;
    cout << "Input file name:";
    cin >> name;
    name = "Inputs//" + name;
    if (argc > 1 && (string(argv[1]) == "-a")) {
        ifstream file(name);
        basic_ofstream<wchar_t> ofs("Outputs//out_Unicode.txt");
        ofs.imbue(loc);
        ofs << (wchar_t)0xfeff;
        string str;
        while (getline(file, str))
        {
            ofs << ansi2unicode(str);
        }
    }
    else {
        wifstream file(name);
        file.imbue(loc);
        file.seekg(2);
        ofstream ofs("Outputs//out_ANSI.txt");
        wstring str;
        while (getline(file, str))
        {
            ofs << unicode2ansi(str);
        }
    }
    cout << "Done!"<<endl;
    return 0;
}
