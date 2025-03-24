/*----------------------------------------------------------------------------
	GetMenuItemID API DOS command              hhokawa@gmail.com
	   
----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct tagOPTION {
	DWORD	dwOptFlags;
	HWND	hWnd;
	int		nPos;
} OPTION;

OPTION	opt;

/*----------------------------------------------------------------------------
	Main
----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	UINT ret;
	int nPos;
	int cnt;
	HMENU hMenu;
//	MENUITEMINFO menuInfo;
	int 	iCt;

	if(argc < 3){
		return -2;
	}
	iCt=1;
	opt.hWnd   = (HWND)atoi(argv[iCt++]);
	hMenu = GetMenu(opt.hWnd);
	if( NULL == hMenu ) { printf("%s\n", "no menu"); return -1; }	
	for( ; iCt < argc - 1 ; iCt++) {
		nPos = atoi(argv[iCt]);
		cnt = GetMenuItemCount(hMenu);
		if( nPos >= cnt ) { printf("%s\n", "index over"); return -1; }
		hMenu = GetSubMenu(hMenu,nPos);
		if( NULL == hMenu ) { printf("%s\n", "not submenu"); return -1; }	
	}

//	ZeroMemory(&menuInfo,sizeof(MENUITEMINFO));
//	menuInfo.cbSize = sizeof(MENUITEMINFO);
//	menuInfo.fMask = MIIM_STATE;
//	ret = GetMenuItemInfo(hMenu, 0, MF_BYPOSITION, &menuInfo);

	nPos = atoi(argv[iCt]);
	ret = GetMenuItemID(hMenu, nPos);
	if( -1 == ret ) { printf("%s\n", "submenu"); return -1; }
	printf("%d\n", ret);
	return 0;
}
