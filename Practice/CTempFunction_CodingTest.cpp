#include "CTempFunction_CodingTest.h"
#include <numeric> //accumulate 사용

CTempFunction_CodingTest::CTempFunction_CodingTest()
{
}

CTempFunction_CodingTest::~CTempFunction_CodingTest()
{
}

void CTempFunction_CodingTest::initialize()
{
  auto arr_title = build_array(_T("1. baekjoon 문제")
    , _T("2. 프로그래머스 문제")
    , _T("")
    , _T("99. EXIT"));
  m_list_title.insert(m_list_title.end(), arr_title.begin(), arr_title.end());
  init_func();
  init_selected_func();
}

void CTempFunction_CodingTest::init_func(void)
{

}

void CTempFunction_CodingTest::init_selected_func(void)
{

}

void CTempFunction_CodingTest::render()
{
  auto shar_title = m_map_selected_func[static_cast<size_t>(COMMON_SELECTED_FUNC::PRINT_TITLE)](nullptr);
  CTempFunction::render(*(TString*)shar_title.get());
}

void CTempFunction_CodingTest::render(const void* _p_void)
{
}

int CTempFunction_CodingTest::update(int _event)
{
    return 0;
}

void CTempFunction_CodingTest::release()
{
}
