/*----------------------------------------------------------------------------
	EnumWindows API DOS command              hhokawa@gmail.com
----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define MAXBUFFSIZE		255
#define OPT_NODATA		(0x00000000L)
#define OPT_TEXT		(0x00000001L)
#define OPT_CLASS		(0x00000002L)
#define OPT_PARENT		(0x00000004L)
#define ERROR_DISPHELP	-1000
typedef struct tagOPTION {
	DWORD	dwOptFlags;
	char	szSelfCmdName[MAXBUFFSIZE*2];
	char	szText[MAXBUFFSIZE];
	char	szClass[MAXBUFFSIZE];
	HWND	hParentWnd;
	UINT	uMsg;
	WPARAM	wParam;
	LPARAM	lParam;
} OPTION;

	OPTION	opt;

/*----------------------------------------------------------------------------
	EnumWindows
----------------------------------------------------------------------------*/
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	char	szClass[MAXBUFFSIZE];
	char	szText[MAXBUFFSIZE];
	HWND	hParentWnd;
	int		ret;
	int		found;

	ret = 1; found = 0;
	if( 0 != (opt.dwOptFlags & OPT_CLASS ) ){
		GetClassName(hWnd, szClass, sizeof(szClass));
		if (0 != strcmp(szClass,opt.szClass)){
			return 1;
		}
		
	}
	if( 0 != (opt.dwOptFlags & OPT_TEXT ) ){
		GetWindowText(hWnd, szText, sizeof(szText));
		if (NULL == strstr(szText,opt.szText)){
			return 1;
		}
		if (NULL != strstr(szText,opt.szSelfCmdName)){
			return 1;
		}
	}
	if( 0 != (opt.dwOptFlags & OPT_PARENT ) ){
		hParentWnd = GetParent(hWnd);
		if (opt.hParentWnd != hParentWnd){
			return 1;
		}
	}

	printf("%ld\n", hWnd);
/*	printf("%s\n", opt.szText);
	printf("%s\n", szText);
*/
	return 1;
}
/*----------------------------------------------------------------------------
	Read arguments
----------------------------------------------------------------------------*/

LRESULT ReadArgment(int argc, char *argv[])
{
	int 	iCt;
	LPSTR	lpszOption;
	LRESULT lResult = ERROR_INVALID_PARAMETER;

//	if(argc < 3){
//		return ERROR_DISPHELP;
//	}

	*opt.szText    = '\0';
	*opt.szClass   = '\0';
	opt.dwOptFlags = OPT_NODATA;
	for(iCt = 1; iCt < argc; iCt += 2){
		if((*argv[iCt] == '-') || (*argv[iCt] == '/')){
			lpszOption = (argv[iCt] + 1);
			if(strcmp(lpszOption, "win") == 0){
				if( iCt + 1 >= argc ) {return lResult;}
				strcpy(opt.szText, argv[iCt+1]);
				opt.dwOptFlags |= OPT_TEXT;
			}
			else if(strcmp(lpszOption, "cls") == 0){
				if( iCt + 1 >= argc ) {return lResult;}
				strcpy(opt.szClass, argv[iCt+1]);
				opt.dwOptFlags |= OPT_CLASS;
			}
			else if(strcmp(lpszOption, "parent") == 0){
				if( iCt + 1 >= argc ) {return lResult;}
				opt.hParentWnd = (HWND)atoi(argv[iCt+1]);
				opt.dwOptFlags |= OPT_PARENT;
			}
		}
	}
	strcpy(opt.szSelfCmdName, argv[0]);
	lResult = ERROR_SUCCESS;
	return lResult;
}
/*----------------------------------------------------------------------------
	Main
----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	LRESULT lResult;

	if((lResult = ReadArgment(argc, argv)) != ERROR_SUCCESS){
		return -1;
	}

	EnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)0);
	return 0;
}
