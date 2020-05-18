#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <locale.h>

#define bSize 1024
#define maxNumberOfFiles 10



void incorrect_input() {
		printf("Only 2 arguments:\n");
	printf("a = pack files\n");
	printf("u = unpack files\n");
	exit(0);
}

void print_problems() {
	setlocale(LC_ALL, "Russian");
	LPVOID e_mess;
	DWORD e_code = GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		e_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&e_mess, 0, NULL);
	char* err_mess = (char*)e_mess;
	wprintf(L"ERROR was generated: failed with 0x%x code\n", e_code);
	wprintf(L"ERROR formatted message: %s\n", err_mess);
}

bool pack_files()
{
	bool result = true;
	LPSTR* inputFiles = new CHAR * [maxNumberOfFiles];
	int inputFilesCount;
	printf("Input number of files, which will archive: ");
	scanf("%d", &inputFilesCount);
	printf("Input full path to files, which will archive\n");
	LPSTR fileName = new CHAR[MAX_PATH];
	for (int i = 0; i < inputFilesCount; i++){
		printf("Input full path to file:");
		scanf("%s", fileName);
		inputFiles[i] = new CHAR[MAX_PATH];
		strcpy(inputFiles[i], fileName);
	}
	LPSTR archiveName = new CHAR[MAX_PATH];
	printf("Input full path to new archive: ");
	scanf("%s", archiveName);
	HANDLE hInReadPipe;
	HANDLE hInWritePipe;
	HANDLE hOutReadPipe;
	HANDLE hOutWritePipe;
	CreatePipe(
		&hInReadPipe,                               
		&hInWritePipe,              
		NULL,	       
		0);	       
	CreatePipe(&hOutReadPipe, &hOutWritePipe, NULL, 0);
	if (hInReadPipe == INVALID_HANDLE_VALUE || hInWritePipe == INVALID_HANDLE_VALUE ||
		hOutReadPipe == INVALID_HANDLE_VALUE || hOutWritePipe == INVALID_HANDLE_VALUE){
		print_problems();
		result = false;
	}
	STARTUPINFOA startInfo;
	ZeroMemory(&startInfo, sizeof(startInfo));
	startInfo.cb = sizeof(startInfo);		
	startInfo.hStdInput = hInReadPipe;		
	startInfo.hStdOutput = hOutWritePipe;	
	startInfo.hStdError = hOutWritePipe;
	startInfo.dwFlags |= STARTF_USESTDHANDLES;
	PROCESS_INFORMATION procInfo;
	ZeroMemory(&procInfo, sizeof(procInfo));
	LPSTR cmdLine = new CHAR[MAX_PATH];
	ZeroMemory(cmdLine, MAX_PATH);
	strncpy(cmdLine, "7z.exe a ", MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, archiveName, MAX_PATH - strlen(cmdLine));
	for (int i = 0; i < inputFilesCount; i++)
	{
		strncat(cmdLine, " ", MAX_PATH - strlen(cmdLine));
		strncat(cmdLine, inputFiles[i], MAX_PATH - strlen(cmdLine));
	}
	strncat(cmdLine, " ", MAX_PATH - strlen(cmdLine));
	if (!CreateProcessA(NULL, cmdLine, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startInfo, &procInfo)){
		print_problems();
		result = false;
	}
	if (result){
		WaitForSingleObject(procInfo.hProcess, INFINITE);
		DWORD readBytes = 0;
		LPSTR outBuffer = new CHAR[bSize];
		ZeroMemory(outBuffer, bSize);
		OVERLAPPED overlapped;
		ReadFile(hOutReadPipe, outBuffer, bSize, &readBytes, &overlapped);
		CloseHandle(procInfo.hProcess);
		CloseHandle(procInfo.hThread);
	}
	CloseHandle(hOutReadPipe);
	CloseHandle(hOutWritePipe);
	CloseHandle(hInReadPipe);
	CloseHandle(hInWritePipe);
	return result;
}

bool unpack_files()
{
	bool result = true;
	LPSTR inputFileName = new CHAR[MAX_PATH];
	LPSTR outputFileName = new CHAR[MAX_PATH];
	printf("Input full path to archive: ");
	scanf("%s", inputFileName);
	printf("Input full output path: ");
	scanf("%s", outputFileName);
	LPSTR cmdLine = new CHAR[MAX_PATH];
	ZeroMemory(cmdLine, MAX_PATH);
	strncpy(cmdLine, "7z.exe e ", MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, inputFileName, MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, " -o", MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, outputFileName, MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, " -y", MAX_PATH - strlen(cmdLine));
	STARTUPINFOA startInfo;
	ZeroMemory(&startInfo, sizeof(startInfo));
	startInfo.cb = sizeof(startInfo);
	startInfo.dwFlags |= STARTF_USESTDHANDLES;
	PROCESS_INFORMATION procInfo;
	ZeroMemory(&procInfo, sizeof(procInfo));
	if (!CreateProcessA(NULL, cmdLine, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startInfo, &procInfo)){
		print_problems();
		result = false;
	}
	return result;
}
int main(int argc, char* argv[])
{
	if (argc != 2 || ((strcmp(argv[1], "-a") != 0) && (strcmp(argv[1], "-u")) != 0)) {
		incorrect_input();
	}
	if (strcmp(argv[1], "-a") == 0) {
		(pack_files()) ? printf("The files were archived.") : printf("The files were not archived.");
	} else {
		(unpack_files()) ? printf("The files were unziped.") : printf("The files were not unziped.");
	}
	return 0;
}
