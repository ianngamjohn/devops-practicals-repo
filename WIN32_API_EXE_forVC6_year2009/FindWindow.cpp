/*----------------------------------------------------------------------------
	FindWindow API DOS command              hhokawa@gmail.com
	    Modified http://www.xs4all.nl/~nd/dekkerware/console/FindWindow.cpp
----------------------------------------------------------------------------*/
#include <stdio.h>		// Including fflush, fputs, printf and fprintf
#include <stdlib.h>		// Including EXIT_SUCCESS and EXIT_FAILURE
#include <windows.h>	// // Including the Windows API FindWindow

int main(int argc, char* argv[]){
	if ( argc <= 1 ){return EXIT_FAILURE;}
	
	unsigned long hWnd;
	const char * pszClassName = NULL;
	const char * pszWindowTitle = NULL;
	DWORD dwErrorCode;
	if ( argc > 1 ){
		pszClassName = argv[1];
		if ( (pszClassName != NULL) && (pszClassName[0] == '\0') ){
			// If the first command-line argument is an empty string, any
			// class name should match when calling the FindWindow API.
			pszClassName = NULL;
		}
		if ( argc > 2 )	{
			pszWindowTitle = argv[2];
		}
	}
	SetLastError(0);
	// MSVC++ 2003 compiler has detected a 64-bit portability issue,
	// warning C4311: 'type cast' : pointer truncation from 'HWND' to
	// 'unsigned long'
	hWnd = (unsigned long)FindWindow(pszClassName, pszWindowTitle);
	dwErrorCode = GetLastError();

	if ( dwErrorCode == 0 && hWnd != 0){
		printf("%ld", hWnd );
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
