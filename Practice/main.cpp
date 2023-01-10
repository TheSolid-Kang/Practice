#include "Headers.h"
#include "CPracticeMgr.h"
#include "CTempFunctionMgr.h"
#include "Headers.h"
#include "Enum.h"

void PrintTitle();

int main() {
#if UNICODE
	std::locale::global(std::locale(".UTF-8"));
#endif
	auto& instance = (*CPracticeMgr::GetInstance());
	do {
		PrintTitle();
		int num = CIO::ask_and_return_integer();
		if (num == EXIT)
			break;
		instance.SetPractice(num);
	} while (instance.Execute() != -1); 

	instance.DestroyInstance();
	(*CTempFunctionMgr::GetInstance()).DestroyInstance();
	return EXIT_SUCCESS;
}

void PrintTitle()
{
	std::list<TString> list_title;

	list_title.emplace_back(_T("1. Practice 1. baekjoon 문제지 출력 구상"));
	list_title.emplace_back(_T("2. Practice 2. "));
	list_title.emplace_back(_T(""));
	list_title.emplace_back(_T(""));
	list_title.emplace_back(_T("99.EXIT"));

	std::for_each(list_title.cbegin(), list_title.cend(), [](auto& _title) {std::tcout << _title << std::endl; });
}
