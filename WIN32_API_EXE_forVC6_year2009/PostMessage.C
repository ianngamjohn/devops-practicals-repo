/*----------------------------------------------------------------------------
	PostMessage API DOS command              hhokawa@gmail.com
----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct tagOPTION {
	DWORD	dwOptFlags;
	HWND	hWnd;
	UINT	uMsg;
	WPARAM	wParam;
	LPARAM	lParam;
} OPTION;

OPTION	opt;

/*----------------------------------------------------------------------------
	Read arguments
----------------------------------------------------------------------------*/
LRESULT ReadArgment(int argc, char *argv[])
{
	int 	iCt;
	LRESULT lResult = ERROR_INVALID_PARAMETER;

	if(argc != 5){
		return lResult;
	}
	iCt=1;
	opt.hWnd   = (HWND)atoi(argv[iCt]);
	opt.uMsg   = (UINT)atoi(argv[iCt+1]);
	opt.wParam = (WPARAM)atoi(argv[iCt+2]);
	opt.lParam = (LPARAM)atoi(argv[iCt+3]);

	return ERROR_SUCCESS;
}

/*----------------------------------------------------------------------------
	Main
----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{

	LRESULT ret;
	if(ERROR_SUCCESS != ReadArgment(argc, argv) ){
		return -1;
	}

	ret = PostMessage(opt.hWnd, opt.uMsg, opt.wParam, opt.lParam);
	printf("%ld\n", ret);
	return 0;
}
