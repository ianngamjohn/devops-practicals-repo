/*----------------------------------------------------------------------------
	GetForegroundWindow              hhokawa@gmail.com
----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define MAXBUFFSIZE		255
char	szClass[MAXBUFFSIZE];
/*----------------------------------------------------------------------------
	Main
----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	HWND hWnd;
	hWnd = GetForegroundWindow();
	printf("%ld", hWnd);
	return 0;
}
