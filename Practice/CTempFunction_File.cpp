#include "CTempFunction_File.h"

CTempFunction_File::CTempFunction_File()
{
}

CTempFunction_File::~CTempFunction_File()
{
}

void CTempFunction_File::initialize()
{
  auto arr_title = build_array( _T("1. TEST FUNCTION 출력 확인")
    , _T("")
    , _T("")
    , _T("99. EXIT") );
  m_list_title.insert(m_list_title.end(), arr_title.begin(), arr_title.end());
  init_func();
  init_selected_func();
}

void CTempFunction_File::init_func(void)
{
	m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::ROOT), [&](const void* _p_void) -> std::shared_ptr<void> {
		StringBuilder str_buil;
		std::for_each(m_list_title.cbegin(), m_list_title.cend(), [&str_buil](const TString& _ch_page) { str_buil.append_endl(_ch_page); });
		TString title = str_buil.str();
		auto shar_title = std::make_shared<TString>(title);
		return shar_title;
		}));

}


void CTempFunction_File::init_selected_func(void)
{
	//COMMON 사용하는 예시임. 
	//사용 할 생각은 없음
	m_map_selected_func.emplace(std::make_pair(static_cast<size_t>(SELECTED_FUNC::ROOT), [&](const void* _p_void) -> std::shared_ptr<void> {
		return m_map_func[static_cast<size_t>(COMMON_FUNC::PRINT_TITLE)](nullptr);
		}));
}


int CTempFunction_File::render()
{
	auto shar_title = m_map_selected_func[static_cast<size_t>(COMMON_FUNC::PRINT_TITLE)](nullptr);
	CTempFunction::render(*(TString*)shar_title.get());
  return 0;
}

int CTempFunction_File::update()
{
    return 0;
}

void CTempFunction_File::release()
{
}
