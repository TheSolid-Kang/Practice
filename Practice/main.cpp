#include "Headers.h"
#include "CPracticeMgr.h"
#include "CTempFunctionMgr.h"
#include "Enum.h"

void PrintTitle(int _selected_mgr = 0);

#pragma region
enum class SELECTED_MGR : int { PRACTICE = 1, TEMP_FUNCTION, END};
int main() {
#if UNICODE
	std::locale::global(std::locale(".UTF-8"));
#endif
	auto& practice_instance = (*CPracticeMgr::GetInstance());
	auto& tfunction_instance = (*CTempFunctionMgr::GetInstance());
	int selected_mgr = 0;
	while (EXIT != selected_mgr)
	{
		PrintTitle();
		selected_mgr = CIO::ask_and_return_integer();

		if (EXIT == selected_mgr)
			break;
		else if (static_cast<int>(SELECTED_MGR::PRACTICE) == selected_mgr)
		{
			do {
				PrintTitle(selected_mgr);
				int num = CIO::ask_and_return_integer();
				if (EXIT == num)
					break;
				practice_instance.SetPractice(num);
			} while (practice_instance.Execute() != -1);
		}
		else if(static_cast<int>(SELECTED_MGR::TEMP_FUNCTION) == selected_mgr)
		{
			do {
				PrintTitle(selected_mgr);
				int num = CIO::ask_and_return_integer();
				if (EXIT == num)
					break;
				tfunction_instance.SetTempFunction(num);
			} while (tfunction_instance.Execute() != -1);
		}
	}
	practice_instance.DestroyInstance();
	tfunction_instance.DestroyInstance();
	return EXIT_SUCCESS;
}
#pragma endregion CONSOLE


#pragma region
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wndClass;
	HWND hwnd;
	MSG msg = { 0 };

	//윈도우 클래스 초기화 및 운영체제에 등록


	//윈도우 생성 후 화면에 출력


	//메시지 큐에 담긴 메시지 처리


	return msg.wParam;
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

#pragma endregion WIN32API

void PrintTitle(int _selected_mgr)
{
	std::list<TString> list_title;


	if (static_cast<int>(SELECTED_MGR::PRACTICE) == _selected_mgr)
	{
		list_title.emplace_back(_T(""));
		list_title.emplace_back(_T("1. Practice: "));
		list_title.emplace_back(_T("2. Practice: "));
		list_title.emplace_back(_T(""));
		list_title.emplace_back(_T(""));
		list_title.emplace_back(_T("99.EXIT"));
	}
	else if (static_cast<int>(SELECTED_MGR::TEMP_FUNCTION) == _selected_mgr)
	{
		list_title.emplace_back(_T(""));
		list_title.emplace_back(_T("1. 파일 관련 함수 모음"));
		list_title.emplace_back(_T("2. 코테 관련 함수 모음"));
		list_title.emplace_back(_T("3. 서버 관련 함수 모음: 파이프 서버"));
		list_title.emplace_back(_T("4. 클라이언트 관련 함수 모음: 파이프 클라이언트"));
		list_title.emplace_back(_T(""));
		list_title.emplace_back(_T(""));
		list_title.emplace_back(_T("99.EXIT"));
	}
	else
	{
		list_title.emplace_back(_T(""));
		list_title.emplace_back(_T("1. Practice"));
		list_title.emplace_back(_T("2. TempFunction"));
		list_title.emplace_back(_T(""));
		list_title.emplace_back(_T("99.EXIT"));
	}

	system("pause");
	system("cls");
	std::for_each(list_title.cbegin(), list_title.cend(), [](auto& _title) {std::tcout << _title << std::endl; });
}
