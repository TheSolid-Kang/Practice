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
	m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::ROOT), [&](const void* _p_void) -> std::shared_ptr<void> {
		StringBuilder str_buil;
		std::for_each(m_list_title.cbegin(), m_list_title.cend(), [&str_buil](const TString& _ch_page) { str_buil.append_endl(_ch_page); });
		TString title = str_buil.str();
		auto shar_title = std::make_shared<TString>(title);

		//auto item = std::accumulate(m_list_title.begin(), m_list_title.end(), std::unique_ptr<TCHAR>(std::make_unique<TCHAR>(_T("")))
		//	, [](std::unique_ptr<TCHAR> _p_ch, TString& _p) {
		//		auto str_title = (*_p_ch) + _p;
		//		auto uniq_titles = std::unique_ptr<TCHAR>(const_cast<TCHAR*>(str_title.c_str()));
		//		return _p_ch;
		//	});

		return shar_title;
		}));
}

void CTempFunction_CodingTest::init_selected_func(void)
{
	m_map_selected_func.emplace(std::make_pair(static_cast<size_t>(SELECTED_FUNC::ROOT), [&](const void* _p_void) -> std::shared_ptr<void> {
		return m_map_func[static_cast<size_t>(FUNC::ROOT)](nullptr);
		}));
}

int CTempFunction_CodingTest::render()
{
    return 0;
}

int CTempFunction_CodingTest::update()
{
    return 0;
}

void CTempFunction_CodingTest::release()
{
}
