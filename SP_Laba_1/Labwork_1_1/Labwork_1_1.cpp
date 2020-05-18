#include "pch.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>

using namespace std;

void ErrorExit(const char* lpszFunction)
{
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);
    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%S failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw);
}
int main(int argc, char *argv[])
{
    setlocale(LC_CTYPE, "rus");
    if (argc > 1 && (string(argv[1]) == "-s")) {

        SYSTEM_INFO siSysInfo;
        GetNativeSystemInfo(&siSysInfo);

        printf("Информация о системе: \n");
        printf("  Архитектура процессора: %u\n", siSysInfo.wProcessorArchitecture);
        printf("  где 9 -- x64 (AMD or Intel)\n");
        printf("  Размер страницы: %u\n", siSysInfo.dwPageSize);
        printf("  Минимальный адрес для приложений: %lx\n",
            siSysInfo.lpMinimumApplicationAddress);
        printf("  Максимальный адрес для приложений: %lx\n",
            siSysInfo.lpMaximumApplicationAddress);
        printf("  Количество логических процессоров в текущей группе: %u\n",
            siSysInfo.dwNumberOfProcessors);
        printf("  маска активного процессора: %u\n",
            siSysInfo.dwActiveProcessorMask);
        printf("  Уровень процессора: %u\n", siSysInfo.wProcessorLevel);
        printf("  Ревизия процессора: %u\n", siSysInfo.wProcessorRevision);
    }
    else {
        if (!GetProcessId(NULL)) {
            ErrorExit("GetProcessId");
        }
    }

}
