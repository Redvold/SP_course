#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "windows.h"
#include <stdio.h>
#include "shlwapi.h"
#include "TCHAR.h"

#define PATH_MAX_LENGHT (MAX_PATH + 1)

void PrintMenu();
bool ChangeDirectory(TCHAR* sCurrDirectory, BOOL isStdinContainNewlineChar);
bool PrintDirectoryContent(TCHAR sCurrDirectory[]);
void ReadPath(TCHAR sBuffNewPath[], BOOL isUsedBeforeInputChar);
bool CreateDirectoryOwn(BOOL isStdinContainNewlineChar);
bool CopyFileOwn(BOOL isStdinContainNewlineChar);
bool DeleteEmptyDirectoryOrFile(BOOL isStdinContainNewlineChar);
bool PrintDetailedInfoAboutFile(BOOL isStdinContainNewlineChar);
void ShowError();

using namespace std;

int main()
{
    setlocale(LC_ALL, ".OCP");
    TCHAR sCurrentPath[PATH_MAX_LENGHT]{ '\0' };

    GetCurrentDirectory(PATH_MAX_LENGHT, sCurrentPath);
    char menuChoice;
    while (1)
    {
        PrintMenu();
        wcout << "Current path:" << sCurrentPath << endl;
        wcout << "Input choice:";
        cin >> menuChoice;

        switch (menuChoice)
        {
        case 'a':
        {
            if (!ChangeDirectory(sCurrentPath, TRUE))
            {
                ShowError();
            }
        } break;
        case 'b':
        {
            if (!PrintDirectoryContent(sCurrentPath))
            {
                ShowError();
            }
        } break;
        case 'c':
        {
            if (!CopyFileOwn(TRUE))
            {
                ShowError();
            }
        } break;
        case 'd':
        {
            if (!CreateDirectoryOwn(TRUE))
            {
                ShowError();
            }
        } break;
        case 'e':
        {
            if (!DeleteEmptyDirectoryOrFile(TRUE))
            {
                ShowError();
            }
        } break;
        case 'f':
        {
            if (!PrintDetailedInfoAboutFile(TRUE))
            {
                ShowError();
            }
        } break;
        case 'g':
        {
            return 0;
        } break;
        default:
        {
            cout << "Error! Incorrect menu choice\n";
        } break;
        }
    }
    return 1;
}

bool ChangeDirectory(TCHAR* sCurrDirectory, BOOL isStdinContainNewlineChar)
{
    TCHAR sBuffNewPath[PATH_MAX_LENGHT];
    cout << "Input new path:";
    ReadPath(sBuffNewPath, isStdinContainNewlineChar);
    if (PathIsDirectory(sBuffNewPath) == FALSE)
    {
        wcout << sBuffNewPath << endl;
        return false;
    }
    wcscpy(sCurrDirectory, sBuffNewPath);
    return true;
}

bool PrintDirectoryContent(TCHAR sCurrDirectory[])
{
    TCHAR sBuff[PATH_MAX_LENGHT];
    HANDLE hFiles;
    WIN32_FIND_DATAW fd;
    _sntprintf(sBuff, PATH_MAX_LENGHT, L"%s\\*\0", sCurrDirectory);
    hFiles = FindFirstFile(sBuff, &fd);
    if (hFiles != INVALID_HANDLE_VALUE)
    {
        wcout << "Directory files:\n";
        do
        {
            if ((wcscmp(L".", fd.cFileName) == 0) || (wcscmp(L"..", fd.cFileName) == 0))
                continue;
            wcout << " - " << fd.cFileName << endl;
        } while (FindNextFile(hFiles, &fd));
        FindClose(hFiles);
        return true;
    }
    return false;
}

bool CreateDirectoryOwn(BOOL isStdinContainNewlineChar)
{
    TCHAR sBuffNewPath[PATH_MAX_LENGHT];
    cout << "Input new directory name:";
    ReadPath(sBuffNewPath, isStdinContainNewlineChar);
    if (!CreateDirectory(sBuffNewPath, NULL))
    {
        return false;
    }
    return true;
}

bool CopyFileOwn(BOOL isStdinContainNewlineChar)
{
    TCHAR sExistFilePath[PATH_MAX_LENGHT];
    TCHAR sNewFilePath[PATH_MAX_LENGHT];
    wcout << "Input path to existing file:\n";
    ReadPath(sExistFilePath, isStdinContainNewlineChar);
    if (!PathFileExists(sExistFilePath))
    {
        cout << "File don`t exist\n";
        return false;
    }
    wcout << "Input new file path:\n";
    ReadPath(sNewFilePath, FALSE);
    if (!CopyFile(sExistFilePath, sNewFilePath, TRUE))
    {
        return false;
    }
    return true;
}

bool DeleteEmptyDirectoryOrFile(BOOL isStdinContainNewlineChar)
{
    TCHAR sPathToDeleting[PATH_MAX_LENGHT];
    wcout << "Input full path to empty directory or file for deleting:\n";
    ReadPath(sPathToDeleting, isStdinContainNewlineChar);
    if (!RemoveDirectory(sPathToDeleting))
    {
        if (!DeleteFile(sPathToDeleting))
        {
            return false;
        }
    }
    return true;
}

bool PrintDetailedInfoAboutFile(BOOL isStdinContainNewlineChar)
{
    WIN32_FIND_DATA fd = { 0 };
    SYSTEMTIME st = { 0 };
    TCHAR sPathToDeleting[PATH_MAX_LENGHT];
    wcout << "Input path to file for detailed info:\n";
    ReadPath(sPathToDeleting, isStdinContainNewlineChar);
    if (!FindFirstFile(sPathToDeleting, &fd))
    {
        return false;
    }
    wcout << "\t Info about file:\n" << fd.cFileName << endl;
    wcout << "Filename for DOS(alternative name):" << fd.cAlternateFileName << endl;
    wcout << "File size:" << ((fd.nFileSizeHigh * MAXDWORD) + fd.nFileSizeLow) / 1024 << " KB" << endl;
    if (FileTimeToSystemTime(&fd.ftCreationTime, &st))
        wprintf_s(L"Creation time:%d %d %d, %d:%d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute);
    if (FileTimeToSystemTime(&fd.ftLastAccessTime, &st))
        wprintf_s(L"Last access time:%d %d %d, %d:%d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute);
    if (FileTimeToSystemTime(&fd.ftLastWriteTime, &st))
        wprintf_s(L"Last write time:%d %d %d, %d:%d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute);
    wcout << "File attributes:\n";
    if (fd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
        wcout << " - Archive\n";
    if (fd.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED)
        wcout << " - Compressed\n";
    if (fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
        wcout << " - Hidden\n";
    if (fd.dwFileAttributes & FILE_ATTRIBUTE_NORMAL)
        wcout << " - Normal\n";
    if (fd.dwFileAttributes & FILE_ATTRIBUTE_OFFLINE)
        wcout << " - Unenable file data\n";
    if (fd.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
        wcout << " - Readonly\n";
    if (fd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)
        wcout << " - System\n";
    if (fd.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)
        wcout << " - Temporary\n";
    return true;
}

void PrintMenu()
{
    cout << "\t File MANAGER\n";
    cout << "a - change\n";
    cout << "b - print\n";
    cout << "c - copy file\n";
    cout << "d - create\n";
    cout << "e - delete file or empty directory\n";
    cout << "f - print  information\n";
    cout << "g - exit\n";
}

void ReadPath(TCHAR sBuffNewPath[], BOOL isUsedBeforeInputChar)
{
    memset(sBuffNewPath, '\0', sizeof(sBuffNewPath));
    if (isUsedBeforeInputChar)
        getchar();
    fgetws(sBuffNewPath, PATH_MAX_LENGHT, stdin);
    sBuffNewPath[(wcschr(sBuffNewPath, '\n') - sBuffNewPath)] = '\0';
}

void ShowError()
{
    LPVOID lpMsgBuf;
    DWORD dwLastError = GetLastError();
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, dwLastError,
        MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
        (LPTSTR)&lpMsgBuf, 0, NULL);
    wprintf(L"\n%s\n", lpMsgBuf);
    LocalFree(lpMsgBuf);
    return;
}
