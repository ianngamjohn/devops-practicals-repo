/*----------------------------------------------------------------------------
	GetWindowProcessID DOS command              hhokawa@gmail.com
----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <windows.h>

/*----------------------------------------------------------------------------
	Main
----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	HWND hWnd;
	DWORD dwProcessId = 0;
	DWORD dwThreadId = 0;
	if(1>=argc){return 1;}
	hWnd = (HWND) atol(argv[1]);
	dwThreadId = GetWindowThreadProcessId((HWND)hWnd, (LPDWORD) &dwProcessId);
	printf("%ld\n", dwProcessId);
	return 0;
}
