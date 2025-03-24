/*----------------------------------------------------------------------------
	SendMessage API DOS command              hhokawa@gmail.com
----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct tagOPTION {
	DWORD	dwOptFlags;
	HWND	hWnd;
	UINT	uMsg;
	WPARAM	wParam;
	char	*lParamStr;
	LPARAM	lParam;
} OPTION;

OPTION	opt;

/*----------------------------------------------------------------------------
	Read arguments
----------------------------------------------------------------------------*/
LRESULT ReadArgment(int argc, char *argv[])
{
	int 	iCt;
	int		len;
	LRESULT lResult = ERROR_INVALID_PARAMETER;

	if(argc != 5){
		return lResult;
	}
	iCt=1;
	opt.hWnd   = (HWND)atoi(argv[iCt]);
	opt.uMsg   = (UINT)atoi(argv[iCt+1]);
	opt.wParam = (WPARAM)atoi(argv[iCt+2]);
	len = strlen(argv[iCt+3]);
	if( 5 < len && 0 == strncmp("#str:" , argv[iCt+3] , 5) ){
		opt.lParamStr = malloc(len - 5 + 1);
		strcpy(opt.lParamStr, argv[iCt+3]+5);
	}else{
		opt.lParam = (LPARAM)atoi(argv[iCt+3]);
	}
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

	if ( 0 != opt.lParamStr ) {
		ret = SendMessage(opt.hWnd, opt.uMsg, opt.wParam, (LPARAM)opt.lParamStr);
		free(opt.lParamStr);
	}else{
		ret = SendMessage(opt.hWnd, opt.uMsg, opt.wParam, opt.lParam);
	}
	printf("%ld\n", ret);
	return 0;
}
