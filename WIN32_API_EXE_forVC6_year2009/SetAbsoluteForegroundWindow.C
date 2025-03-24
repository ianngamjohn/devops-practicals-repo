/*----------------------------------------------------------------------------
  Force to ForegroundWindow                hhokawa@gmail.com
      refer =>  http://techtips.belution.com/ja/vc/0012/
----------------------------------------------------------------------------*/
#include <windows.h>
#include <stdio.h>
#include <string.h>
#define SPI_GETFOREGROUNDLOCKTIMEOUT        0x2000
#define SPI_SETFOREGROUNDLOCKTIMEOUT        0x2001

void SetAbsoluteForegroundWindow(HWND hWnd)
{
    int nTargetID, nForegroundID;
    DWORD sp_time;

    // フォアグラウンドウィンドウを作成したスレッドのIDを取得
    nForegroundID = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
    // 目的のウィンドウを作成したスレッドのIDを取得
    nTargetID = GetWindowThreadProcessId(hWnd, NULL );

    // スレッドのインプット状態を結び付ける
    AttachThreadInput(nTargetID, nForegroundID, TRUE );  // TRUE で結び付け

    // 現在の設定を sp_time に保存
    SystemParametersInfo( SPI_GETFOREGROUNDLOCKTIMEOUT,0,&sp_time,0);
    // ウィンドウの切り替え時間を 0ms にする
    SystemParametersInfo( SPI_SETFOREGROUNDLOCKTIMEOUT,0,(LPVOID)0,0);

    // ウィンドウをフォアグラウンドに持ってくる
    SetForegroundWindow(hWnd);

    // 設定を元に戻す
    SystemParametersInfo( SPI_SETFOREGROUNDLOCKTIMEOUT,0,sp_time,0);

    // スレッドのインプット状態を切り離す
    AttachThreadInput(nTargetID, nForegroundID, FALSE );  // FALSE で切り離し
}

/*----------------------------------------------------------------------------
	Main
----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	HWND hWnd;

	if(1>=argc){return 1;}
	hWnd = (HWND) atol(argv[1]);
	SetAbsoluteForegroundWindow((HWND) hWnd);
	return 0;
}
