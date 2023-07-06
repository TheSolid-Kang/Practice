#include "CTempFunction_CodingTest.h"
#include <numeric> //accumulate 사용

CTempFunction_CodingTest::CTempFunction_CodingTest()
{
}

CTempFunction_CodingTest::~CTempFunction_CodingTest()
{
}

void CTempFunction_CodingTest::_Initialize()
{
	auto arr_title = _BuildArray(_T("1. baekjoon 문제")
		, _T("2. 프로그래머스 문제")
		, _T("")
		, _T("99. EXIT"));
	m_list_title.insert(m_list_title.end(), arr_title.begin(), arr_title.end());
	_InitFunc();
	_InitSelectedFunc();
}

void CTempFunction_CodingTest::_InitFunc(void)
{

}

void CTempFunction_CodingTest::_InitSelectedFunc(void)
{

}

void CTempFunction_CodingTest::_Render()
{
	auto shar_title = m_map_selected_func[static_cast<size_t>(COMMON_SELECTED_FUNC::PRINT_TITLE)](nullptr);
	CTempFunction::_Render(*(TString*)shar_title.get());
}

void CTempFunction_CodingTest::_Render(const void* _p_void)
{
}

int CTempFunction_CodingTest::_Update(int _event)
{
	return 0;
}

void CTempFunction_CodingTest::_Release()
{
}
