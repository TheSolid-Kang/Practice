#pragma once
#include <Windows.h>
#include <commdlg.h> //파일 다이얼로그용.
#include <string>
#include <tchar.h>

#include <tchar.h>//ExecuteFile () 
#include <stdio.h>//ExecuteFile () 

#if UNICODE 
using TString = std::wstring;
#else
using TString = std::string;
#endif;

class CFileMgr {
public:
	static TString GetOpenFileDialg() {
		OPENFILENAME OFN;
		TCHAR filePathName[100] = _T("");
		TCHAR lpstrFile[100] = _T("");
		static TCHAR filter[] = _T("모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx");
		HWND hWnd = NULL;

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		//OFN.hwndOwner = hWnd;
		OFN.hwndOwner = hWnd;
		OFN.lpstrFilter = filter;
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 100;
		OFN.lpstrInitialDir = _T(".");

		if (GetOpenFileName(&OFN) != 0) {
			wsprintf(filePathName, _T("%s 파일을 선택하시겠습니까?"), OFN.lpstrFile);
			MessageBox(hWnd, filePathName, _T("열기 선택"), MB_OK);

			TString wstr_result(OFN.lpstrFile); //LPWSTR -> std::wstring

			return wstr_result;//파일 경로 담김
		}
		return L"";
	}
	static void ExecuteFile(const TString& path = GetOpenFileDialg()) {
		HWND hConsole = GetConsoleWindow();
		ShowWindow(hConsole, SW_HIDE);

		SHELLEXECUTEINFO sei;
		ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));

		sei.cbSize = sizeof(SHELLEXECUTEINFO);
		//sei.lpFile =  L"C:\\ManyoneChurch\\msi\\SQLEXPRWT_x64_KOR.exe";
		sei.lpFile = path.c_str();
		sei.lpParameters = _T("");
		sei.nShow = SW_SHOW;
		sei.fMask = SEE_MASK_NOCLOSEPROCESS;
		sei.lpVerb = _T("open");
		DWORD result = ShellExecuteEx(&sei);
		if (sei.hProcess != NULL)
			WaitForSingleObject(sei.hProcess, INFINITE); //여기서 해당 프로세스가 종료될때까지 대기하게됨

		//ShellExecute(NULL, L"open", "C:\\ManyoneChurch\\msi\\sql.bat", NULL, NULL, SW_SHOW);
		//ShellExecute(NULL, _T("open"), path.c_str(), NULL, NULL, SW_SHOW);

	}

};