/*----------------------------------------------------------------------------
	GetClassName              hhokawa@gmail.com
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
	unsigned long p_hWnd;
	if(2!=argc){return 1;}
	p_hWnd = atol(argv[1]);
	GetClassName((HWND) p_hWnd, szClass, sizeof(szClass));
	printf("%s\n", szClass);
	return 0;
}
