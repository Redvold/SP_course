#include <stdio.h>
#include <Windows.h>

int main()
{
    HANDLE myMutex = CreateMutex(
        0,
        0,
        TEXT("MutexName")
    );
    DWORD result = WaitForSingleObject(myMutex, 0);
    if (result != WAIT_OBJECT_0){
        printf("not ok !!!\n");
        return 0;
    } else {
        printf("ok");
        while (1) {}
    }
    return 0;
}
