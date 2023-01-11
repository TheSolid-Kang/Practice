#include "CTempFunction_Server.h"

CTempFunction_Server::CTempFunction_Server()
{
}

CTempFunction_Server::~CTempFunction_Server()
{
}

void CTempFunction_Server::initialize(void)
{
  auto arr_title = build_array(_T("1. 파이프 서버 구현")
    , _T("2. ")
    , _T("")
    , _T("99. EXIT"));
  m_list_title.insert(m_list_title.end(), arr_title.begin(), arr_title.end());
  init_func();
  init_selected_func();
}

void CTempFunction_Server::init_func(void)
{
}

void CTempFunction_Server::init_selected_func(void)
{
}

void CTempFunction_Server::render(void)
{
  auto shar_title = m_map_selected_func[static_cast<size_t>(COMMON_SELECTED_FUNC::PRINT_TITLE)](nullptr);
  CTempFunction::render(*(TString*)shar_title.get());
}

void CTempFunction_Server::render(const void* _p_void)
{
}

int CTempFunction_Server::update(int _event)
{
    return 0;
}

void CTempFunction_Server::release(void)
{
}
