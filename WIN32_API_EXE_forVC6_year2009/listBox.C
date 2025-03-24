/*----------------------------------------------------------------------------
	listBox API DOS command              hhokawa@gmail.com
----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define MAXBUFFSIZE		1024
char	command[MAXBUFFSIZE];
/*----------------------------------------------------------------------------
	get list items
----------------------------------------------------------------------------*/
void getItems(HWND hWnd)
{
	int		i;
	LRESULT		len;
	PSTR	szText2;

	for(i=0;;i++){	/* Display each ListBox item */
		len = SendMessage(hWnd, LB_GETTEXTLEN, (WPARAM) i, 0);
		szText2 = malloc(len + 1);
		len = SendMessage(hWnd, LB_GETTEXT, (WPARAM) i, (LPARAM) szText2);
		if(LB_ERR == len) { free(szText2);break; }
		printf("%s\n", szText2);
		free(szText2);
	}
}
/*----------------------------------------------------------------------------
	Main
----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	unsigned long hWnd;
	if(1>=argc){return 1;}
	hWnd = atol(argv[1]);
	if(3<=argc){
		strcpy(command,argv[2]);
	}
	if(0 == strcmp("getitems",command) || 0 == strcmp("getItems",command)){
		getItems((HWND) hWnd);
	}
	return 0;
}
