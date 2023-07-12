
#ifdef _MY_MFC
#include <afxwin.h>
#elif _MY_WIN32API
#include "Headers.h"
#include "CPracticeMgr.h"
#include "CTempFunctionMgr.h"
#endif

#ifdef _MY_WIN32API
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wndClass;
	HWND hwnd;
	MSG msg = { 0 };

	//윈도우 클래스 초기화 및 운영체제에 등록
	wndClass.style = CS_HREDRAW | CS_VREDRAW;//CS_HREDRAW나 CS_VREDRAW는 클라이언트 영역(작업영역, 사용자 영역)의 폭과 높이가 변경되었을 경우 전부 다시 그리도록 해준다.
	wndClass.lpfnWndProc = WndProc;//함수 
	wndClass.cbClsExtra = NULL;//여분 메모리 0바이트
	wndClass.cbWndExtra = NULL;//여분 메모리 0바이트
	wndClass.hInstance = hInstance; // 매개변수로 받은 인스턴스 핸들
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//아이콘 모양
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//흰색 배경
	wndClass.lpszMenuName = NULL; //메뉴(NULL -> 메뉴 없음)
	wndClass.lpszClassName = TEXT("Hello Class");//윈도우 클래스 이름
	if (false == RegisterClass(&wndClass))
		return 1;

	//윈도우 생성 후 화면에 출력
	hwnd = CreateWindow(TEXT("Hello Class")
		, TEXT("Hellow SDK")
		, WS_OVERLAPPEDWINDOW
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, NULL
		, NULL
		, hInstance
		, NULL);

	ShowWindow(hwnd, nCmdShow);


	//메시지 큐에 담긴 메시지 처리
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	//CloseHandle(hInstance);
	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT massge, WPARAM wParam, LPARAM lPram)
{
	HDC hdc;
	PAINTSTRUCT paint_struct;
	const TCHAR* str = TEXT("Hellow, SDK");

	//발생한 메시지의 종류에 따라 처리하는 로직 구현
	switch (massge)
	{
	case WM_CREATE:
		return 0;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("마우스 클릭"), TEXT("마우스 메시지"), MB_OK);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &paint_struct);
		TextOut(hdc, 100, 100, str, lstrlen(str));
		EndPaint(hwnd, &paint_struct);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	//응용 프로그램이 처리하지 못 한 메시지를 운영체제가 처리하도록 하는 함수
	return DefWindowProc(hwnd, massge, wParam, lPram);
}


#elif _MY_MFC
//initiate application program class
class CMain : public CWinApp
{
public:
	virtual BOOL InitInstance();
};
//initiate main window class
class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
	~CMainFrame();

protected:
	//fx == function
	//application framework
	//tx == treatment
	//rx == receiver
	//tx == transfer
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP();
};
CMain theApp;

BOOL CMain::InitInstance()
{
	m_pMainWnd = new CMainFrame();
	(*m_pMainWnd).ShowWindow(m_nCmdShow);
	return TRUE;
}

CMainFrame::CMainFrame()
{
	Create(NULL, _T("HellowMFC"));
}

CMainFrame::~CMainFrame()
{

}
void CMainFrame::OnPaint()
{
	CPaintDC dc(this);
	const TCHAR* msg = _T("Hellow MFC");
	dc.TextOut(100, 100, msg, lstrlen(msg));
}
void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	MessageBox(_T("마우스 메시지!"), _T("마우스 메시지"));
}
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()
#endif