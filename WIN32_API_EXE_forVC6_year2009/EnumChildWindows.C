/*----------------------------------------------------------------------------
	EnumChildWindows API DOS command              hhokawa@gmail.com
----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define MAXBUFFSIZE		1024
int		classNameSpecified;
char	p_szClass[MAXBUFFSIZE];
int		p_num; int	num;
/*----------------------------------------------------------------------------
	EnumChildWindows
----------------------------------------------------------------------------*/
BOOL CALLBACK EnumChildWindowsProc(HWND hWnd, LPARAM lParam)
{
	char	szClass[MAXBUFFSIZE];
	char	szText[MAXBUFFSIZE];
	int		ret;
	int		displayResult;
	int		i;
	LRESULT		len;
	PSTR	szText2;

	GetClassName(hWnd, szClass, sizeof(szClass));
	GetWindowText(hWnd, szText, sizeof(szText));

	if( classNameSpecified) { /* Class name specified */
		if(0==strcmp(szClass,p_szClass)){ /* Class name match */
			if(0==p_num){
				displayResult=1; ret=TRUE;
			}else{
				num=num+1;
				if(num==p_num){
					displayResult=1; ret = FALSE;
				}else{
					displayResult=0; ret = TRUE;
				}
			}
		}else{ /* Class name not match */
			displayResult=0; ret = TRUE;
		}
	}else{
		displayResult=1; ret=TRUE;
	}

	if(1==displayResult){
//		if(0==strcmp(szClass,"ListBox")){ 
//			printf("%ld\n", hWnd);
//			printf("%s\n", szClass);
//			for(i=0;;i++){	/* Display each ListBox item */
//				len = SendMessage(hWnd, LB_GETTEXTLEN, (WPARAM) i, 0);
//				szText2 = malloc(len + 1);
//				len = SendMessage(hWnd, LB_GETTEXT, (WPARAM) i, (LPARAM) szText2);
//				if(LB_ERR == len) { free(szText2);break; }
//				printf("%s\n", szText2);
//				free(szText2);
//			}
//		}else{
			printf("%ld\n", hWnd);
			printf("%s\n", szClass);
			printf("%s\n", szText);
//		}

	}
	return ret;
}
/*----------------------------------------------------------------------------
	Main
----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	unsigned long p_hWnd;
	classNameSpecified=0;
	p_num = 0;
	num = 0;
	if(1>=argc){return 1;}
	p_hWnd = atol(argv[1]);
	if(3<=argc){
		strcpy(p_szClass,argv[2]);
		classNameSpecified=1;
		if(4<=argc){
			p_num = atoi(argv[3]);
		}
	}
	EnumChildWindows((HWND)p_hWnd, (WNDENUMPROC)EnumChildWindowsProc, (LPARAM)0);
	return 0;
}
