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

}


void CTempFunction_File::init_selected_func(void)
{

}


void CTempFunction_File::render()
{
	auto shar_title = m_map_selected_func[static_cast<size_t>(COMMON_SELECTED_FUNC::PRINT_TITLE)](nullptr);
	CTempFunction::render(*(TString*)shar_title.get());
}

void CTempFunction_File::render(const void* _p_void)
{
}

int CTempFunction_File::update(int _event)
{
    return 0;
}

void CTempFunction_File::release()
{
}
