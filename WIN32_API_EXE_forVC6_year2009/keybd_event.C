/*----------------------------------------------------------------------------
	keybd_event API DOS command              hhokawa@gmail.com
----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct tagOPTION {
	DWORD	dwOptFlags;
	BYTE	bVk;
	BYTE	bScan;
	DWORD	dwFlags;
	DWORD	dwExtraInfo;
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
	opt.bVk   = (BYTE)atoi(argv[iCt]);
	opt.bScan   = (BYTE)atoi(argv[iCt+1]);
	opt.dwFlags = (DWORD)atol(argv[iCt+2]);
	opt.dwExtraInfo = (DWORD)atol(argv[iCt+3]);

	return ERROR_SUCCESS;
}

/*----------------------------------------------------------------------------
	Main
----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{

	if(ERROR_SUCCESS != ReadArgment(argc, argv) ){
		return -1;
	}

	keybd_event(opt.bVk, opt.bScan, opt.dwFlags, opt.dwExtraInfo);

	return 0;
}
