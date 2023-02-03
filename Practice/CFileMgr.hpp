#pragma once
#include <Windows.h>
#include <commdlg.h> //open file dialog
#include <iostream>

#include <string>
#include <tchar.h>

#include <tchar.h>//ExecuteFile () 
#include <stdio.h>//ExecuteFile () 

#include <shlobj_core.h> //open folder dialog
#include <string>
#include <atlcore.h>


#include <fstream>
#include <filesystem>




class CFileMgr {
#if UNICODE 
	using TString = std::wstring;
	using tifstream = std::wifstream;
	using tofstream = std::wofstream;
#define tcout  wcout
#define tcin  wcin
#else
	using TString = std::string;
	using tifstream = std::ifstream;
	using tofstream = std::ofstream;
#define tcout  cout
#define tcin  wcin
#endif;
public:
	static TString GetOpenFileDialg() {
		OPENFILENAME OFN;
		TCHAR filePathName[MAX_PATH] = _T("");
		TCHAR lpstrFile[MAX_PATH] = _T("");
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
		return _T("");
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

	static TString GetOpenFolderDialg(TString _path = (TString)_T("D:\\") ){

		auto BrowseCallbackProc = [](HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData) -> int CALLBACK{
			switch (uMsg)
			{
			case BFFM_INITIALIZED:      // 폴더 선택 대화상자를 초기화 할 때, 초기 경로 설정
			{
			::SendMessage(hWnd, BFFM_SETSELECTION, TRUE, (LPARAM)lpData);
			}
			break;

			// BROWSEINFO 구조체의 ulFlags 값에 BIF_STATUSTEXT 가 설정된 경우 호출
			// 단, BIF_NEWDIALOGSTYLE 가 설정되어 있을 경우 호출되지 않음
			case BFFM_SELCHANGED:       // 사용자가 폴더를 선택할 경우 대화상자에 선택된 경로 표시
			{
			TCHAR szPath[MAX_PATH] = { 0, };

			::SHGetPathFromIDList((LPCITEMIDLIST)lParam, szPath);
			::SendMessage(hWnd, BFFM_SETSTATUSTEXT, 0, (LPARAM)szPath);
			}
			break;

			// BROWSEINFO 구조체의 ulFlags 값에 BIF_VALIDATE 가 설정된 경우 호출
			// BIF_EDITBOX 와 같이 설정된 경우만 호출됨
			case BFFM_VALIDATEFAILED:   // 에디터 콘트롤에서 폴더 이름을 잘못 입력한 경우 호출
			{
			::MessageBox(hWnd, _T("해당 폴더를 찾을 수 없습니다."), _T("오류"),
			MB_ICONERROR | MB_OK);
			}
			break;
			}

			return 0; };

		BROWSEINFO browse_info;
		TCHAR szTemp[MAX_PATH] = _T("");//저장 위치
		TCHAR* pRootPath = const_cast<TCHAR*>(_path.c_str());//시작 위치
		//const_cast<TCHAR*>(_T("D:\\"));//시작 위치
		HWND hWnd = NULL;
		ZeroMemory(&browse_info, sizeof(BROWSEINFO));

		browse_info.hwndOwner = hWnd;
		browse_info.lpszTitle = _T("폴더를 선택해주세요.");
		browse_info.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX
			| BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT | BIF_VALIDATE;
		browse_info.lpfn = BrowseCallbackProc;
		browse_info.lParam = (LPARAM)pRootPath;
		browse_info.pszDisplayName = szTemp;

		LPITEMIDLIST pItemIdList = SHBrowseForFolder(&browse_info);

		if (SHGetPathFromIDList(pItemIdList, szTemp)) {
			MessageBox(hWnd, szTemp, _T("open?"), MB_OK);
			return browse_info.pszDisplayName;//szTemp 
		}

		return _T("");
	}

	static TCHAR* GetFileType(TCHAR* _path) 
	{
		static TCHAR buf[MAX_PATH] = _T("");
		bool ret = false;
		TCHAR* ptr = nullptr;
#if UNICODE
		ptr = wcsrchr(_path, _T('.'));
		if (ptr == nullptr)
			return nullptr; 
		wcscpy(buf, ptr + 1);//wcscpy 함수 사용하기 위해 C++/전처리기: _CRT_SECURE_NO_WARNINGS 추가함.
#else
		ptr = strrchr(_path, _T('.'));
		if (ptr == nullptr)
			return nullptr;
		strcpy(buf, ptr + 1);
#endif



		return buf;
	}

	static std::vector<TString> getTxtFiles(const TString& dirPath) {
		std::vector<TString> txtFiles;
		TString searchPath = dirPath + _T("\\*.txt");
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(searchPath.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				txtFiles.push_back(fd.cFileName);
			} while (::FindNextFile(hFind, &fd));
			::FindClose(hFind);
		}
		return txtFiles;
	}
	//0. 실행파일 경로 구하기
	static TString GetEXEFilePath() {
		//1. 실행파일 경로 구하기 
		TCHAR path[MAX_PATH] = { 0, };
		GetModuleFileName(NULL, path, MAX_PATH);
		TString exe_path = path;
		exe_path = exe_path.substr(0, exe_path.find_last_of(_T("\\/")));
		return exe_path;
	}
	//1-1. Directory 내 파일 생성
	static void CreateNewFile(TString _path, TString _file_name) {
		TString file_path = _path + _file_name;
		tofstream fout = tofstream(file_path);//파일 열기_만약 파일이 없으면 만듦.

		std::tcout << _T("fout.is_open() == ") << fout.is_open() << std::endl;
		if (true == fout.is_open())
			fout.close();
	}
	//1-2. Directory 내 하위 폴더 차례대로 생성
	static void CreateDirectorys(const TString& _path) {
		TString path(_path.begin(), _path.end());
		TCHAR arr_dir_name[256] = { 0, };
		TCHAR* ch_ptr_path = const_cast<TCHAR*>(path.c_str());
		TCHAR* ch_ptr_dirname = arr_dir_name;

		while (*ch_ptr_path) {
			if ((_T('\\') == *ch_ptr_path) || (_T('/') == *ch_ptr_path)) {
				if (_T(':') != *(ch_ptr_path - 1))
					CreateDirectory(arr_dir_name, NULL);
			}
			*ch_ptr_dirname++ = *ch_ptr_path++;
			*ch_ptr_dirname = _T('\0');
		}
		CreateDirectory(arr_dir_name, NULL);
	}


	//2-1. Directory 내 파일 목록 출력
	static std::vector<TString> GetFilesInDirectory(TString& _path) {
		std::vector<TString> vec_files;
		vec_files.reserve(1024);
		auto iter = std::filesystem::directory_iterator(_path);
		while (true != iter._At_end()) {
#if UNICODE 
			vec_files.emplace_back((*iter++).path().wstring());//std::filesystem::path -> std::string 으로 변환
#else
			vec_files.emplace_back((*iter++).path().string());//std::filesystem::path -> std::string 으로 변환
#endif;
		}
		vec_files.shrink_to_fit();
		return vec_files;
	}
	//2-2. Directory 내 파일 목록 출력
	static std::vector<TString> GetRecursiveFilesInDirectory(TString& _path) {
		std::vector<TString> vec_files;
		vec_files.reserve(1024);
		auto iter = std::filesystem::directory_iterator(_path);
		while (true != iter._At_end()) {
			std::filesystem::path file_path = (*iter++).path();
#if UNICODE 
			TString str_file_path = file_path.wstring();//std::filesystem::path -> std::wstring 으로 변환
#else
			TString file_path(file_path.string());//std::filesystem::path -> std::string 으로 변환
#endif;
			if (std::filesystem::is_directory(file_path)) {
				auto vec_recursive_file = GetRecursiveFilesInDirectory(str_file_path);
				vec_files.insert(vec_files.end(), vec_recursive_file.begin(), vec_recursive_file.end());
			}
			else
				vec_files.emplace_back(str_file_path);

		}
		vec_files.shrink_to_fit();
		return vec_files;
	}

};