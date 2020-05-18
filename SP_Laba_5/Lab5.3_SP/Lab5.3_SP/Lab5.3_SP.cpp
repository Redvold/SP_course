#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <ctime>

#define CRITICAL_SECTION_MODE 0
#define NOT_CRITICAL_SECTION_MODE 1

#define numberOfThreads 3
#define amountOfNumbers 10101110

int arr[amountOfNumbers];
CRITICAL_SECTION criricalSection;

void sum()
{
    int sum = 0;
    for (int i = 0; i < amountOfNumbers; i++)
        sum += arr[i];
    printf("Sum - %d\n", sum);
}

void average()
{
    double avg = 0;
    for (int i = 0; i < amountOfNumbers; i++)
        avg += arr[i];
    printf("Avarage - %f\n", avg / amountOfNumbers);
}

void maximum()
{
    int max = 0;
    for (int i = 0; i < amountOfNumbers; i++){
        if (max < arr[i])
            max = arr[i];
    }
    printf("Max - %d\n", max);
}

void generate()
{
    for (int i = 0; i < amountOfNumbers; i++)
        arr[i] = rand() % 100;
}

DWORD WINAPI findSum(LPVOID mode)
{
    if (NOT_CRITICAL_SECTION_MODE) {
        sum();
    }
    else {
        if (!InitializeCriticalSectionAndSpinCount(&criricalSection, 0x00000400)) {
            return 0;
        }
        EnterCriticalSection(&criricalSection);
        sum();
        LeaveCriticalSection(&criricalSection);
    }
    return 0;
}

DWORD WINAPI findAvg(LPVOID mode)
{
    if (NOT_CRITICAL_SECTION_MODE) {
        average();
    }
    else {
        if (!InitializeCriticalSectionAndSpinCount(&criricalSection, 0x00000400)) {
            return 0;
        }
        EnterCriticalSection(&criricalSection);
        average();
        LeaveCriticalSection(&criricalSection);
    }
    return 0;
}

DWORD WINAPI findMax(LPVOID mode)
{

    if (NOT_CRITICAL_SECTION_MODE) {
        maximum();
    }
    else {
        if (!InitializeCriticalSectionAndSpinCount(&criricalSection, 0x00000400)) {
            return 0;
        }
        EnterCriticalSection(&criricalSection);
        maximum();
        LeaveCriticalSection(&criricalSection);
    }
    return 0;
}

void DeleteCriticalSection()
{
    DeleteCriticalSection(&criricalSection);
}

int main()
{
    HANDLE hThread[numberOfThreads];
    DWORD ThreadId;
    clock_t start, finish;

    generate();

    printf("1 - use critical section\n");
    start = clock();
    hThread[0] = CreateThread(NULL, 0, findSum, (LPVOID)CRITICAL_SECTION_MODE, 0, &ThreadId);
    hThread[1] = CreateThread(NULL, 0, findAvg, (LPVOID)CRITICAL_SECTION_MODE, 0, &ThreadId);
    hThread[2] = CreateThread(NULL, 0, findMax, (LPVOID)CRITICAL_SECTION_MODE, 0, &ThreadId);
    WaitForMultipleObjects(numberOfThreads, hThread, TRUE, INFINITE);

    finish = clock();
    double duration = finish - start;
    printf("Time: %f\n\n", duration);

    DeleteCriticalSection();

    for (int i = 0; i < numberOfThreads; i++){
        CloseHandle(hThread[i]);
    }

    printf("2 - not use critical section\n");
    start = clock();

    hThread[0] = CreateThread(NULL, 0, findSum, (LPVOID)NOT_CRITICAL_SECTION_MODE, 0, &ThreadId);
    hThread[1] = CreateThread(NULL, 0, findAvg, (LPVOID)NOT_CRITICAL_SECTION_MODE, 0, &ThreadId);
    hThread[2] = CreateThread(NULL, 0, findMax, (LPVOID)NOT_CRITICAL_SECTION_MODE, 0, &ThreadId);
    WaitForMultipleObjects(numberOfThreads, hThread, TRUE, INFINITE);

    finish = clock();
    duration = finish - start;
    printf("Time: %f\n", duration);

    DeleteCriticalSection();

    for (int i = 0; i < numberOfThreads; i++){
        CloseHandle(hThread[i]);
    }
    return 0;
}
