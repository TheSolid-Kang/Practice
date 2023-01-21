#include "Headers.h"
#include "CPracticeMgr.h"
#include "CTempFunctionMgr.h"

#pragma region WIN32API
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wndClass;
	HWND hwnd;
	MSG msg = { 0 };

	//윈도우 클래스 초기화 및 운영체제에 등록


	//윈도우 생성 후 화면에 출력


	//메시지 큐에 담긴 메시지 처리


	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND _hwnd, UINT _unit_massge, WPARAM _wParam, LPARAM _lPram)
{
	HDC hdc;
	PAINTSTRUCT paint_struct;
	const TCHAR* _p_ch = TEXT("");

	//발생한 메시지의 종류에 따라 처리하는 로직 구현



	//응용 프로그램이 처리하지 못 한 메시지를 운영체제가 처리하도록 하는 함수
	return DefWindowProc(_hwnd, _unit_massge, _wParam, _lPram);
}

#pragma endregion 