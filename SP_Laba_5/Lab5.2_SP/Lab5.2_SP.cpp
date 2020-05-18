#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <locale.h>
#include <ctime>

#define numberOfThreads 10
#define initSemaphoreCount 3
#define maxSemaphoreCount 3

HANDLE semaphore;

void print_problems() {
    setlocale(LC_ALL, "Russian");
    printf("\nSomething went wrong(\n");
    LPVOID e_mess;
    DWORD e_code = GetLastError();
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
        e_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&e_mess, 0, NULL);
    char* err_mess = (char*)e_mess;
    wprintf(L"ERROR was generated: failed with 0x%x code\n", e_code);
    wprintf(L"ERROR formatted message: %s\n", err_mess);
}


DWORD WINAPI ExecutedByThread(LPVOID lpParam)
{
    DWORD state, bytesWritten;
    HANDLE file;
    clock_t start, finish;
    char* string = new char[10];
    bool run = true;
    const int second = 1000;
    state = WaitForSingleObject(semaphore, 3);
    while (run == true)
    {
        if (state == WAIT_OBJECT_0)
        {
            start = clock();
            Sleep(3 * second);
            printf("\nThread - %d is in critical section\n", GetCurrentThreadId());

            file = CreateFileA("result.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            finish = clock();

            double duration = finish - start;

            SetFilePointer(file, 0, NULL, FILE_END);
            sprintf(string, "%f", duration);

            WriteFile(file, string, sizeof(string), &bytesWritten, NULL);

            if (file == INVALID_HANDLE_VALUE){
                print_problems();
            }


            run = false;
            Sleep(3 * second);
            printf("\nThread - %d is not in critical section anymore\n", GetCurrentThreadId());
            if (!ReleaseSemaphore(semaphore, 1, NULL)){
                print_problems();
            }
        }
    }
    return 0;
}

int main()
{
    HANDLE threads[numberOfThreads];
    DWORD id;

    semaphore = CreateSemaphore(
        NULL,
        initSemaphoreCount,
        maxSemaphoreCount,
        NULL
    );

    if (semaphore == NULL){
        print_problems();
        return 1;
    }

    for (int i = 0; i < numberOfThreads; i++)
    {
        threads[i] = CreateThread(NULL, 0, ExecutedByThread, NULL, 0, &id);

        if (threads[i] == NULL){
            print_problems();
            return 1;
        }
    }

    WaitForMultipleObjects(numberOfThreads, threads, TRUE, INFINITE);
    for (int i = 0; i < numberOfThreads; i++)
        CloseHandle(threads[i]);
    CloseHandle(semaphore);
    return 0;
}
