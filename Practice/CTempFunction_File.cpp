#include "CTempFunction_File.h"

CTempFunction_File::CTempFunction_File()
{
}

CTempFunction_File::~CTempFunction_File()
{
}

void CTempFunction_File::_Initialize()
{
  auto arr_title = _BuildArray( _T("1. TEST FUNCTION 출력 확인")
    , _T("")
    , _T("")
    , _T("99. EXIT") );
  m_list_title.insert(m_list_title.end(), arr_title.begin(), arr_title.end());
  _InitFunc();
  _InitSelectedFunc();
}

void CTempFunction_File::_InitFunc(void)
{

}


void CTempFunction_File::_InitSelectedFunc(void)
{

}


void CTempFunction_File::_Render()
{
	auto shar_title = m_map_selected_func[static_cast<size_t>(COMMON_SELECTED_FUNC::PRINT_TITLE)](nullptr);
	CTempFunction::_Render(*(TString*)shar_title.get());
}

void CTempFunction_File::_Render(const void* _p_void)
{
}

int CTempFunction_File::_Update(int _event)
{
    return 0;
}

void CTempFunction_File::_Release()
{
}
