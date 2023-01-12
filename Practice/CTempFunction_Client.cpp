#include "CTempFunction_Client.h"
#define PIPE_NAME "\\\\.\\pipe\\echo"
#define BUF_SIZE 32768

CTempFunction_Client::CTempFunction_Client()
{
}

CTempFunction_Client::~CTempFunction_Client()
{
}

void CTempFunction_Client::initialize(void)
{
  auto arr_title = build_array(_T(" ")
    , _T("1. ")
    , _T("")
    , _T("99. EXIT"));
  m_list_title.insert(m_list_title.end(), arr_title.begin(), arr_title.end());
  init_func();
  init_selected_func();
}

void CTempFunction_Client::init_func(void)
{
  m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::ROOT), [&](const void* _p_void) -> std::shared_ptr<void> {
    return nullptr; }));
  m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::RESPOND_TEMP), [&](const void* _p_void) -> std::shared_ptr<void> {
    return nullptr; }));
  m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::INSPECT_PIPE_HANDLE), [&](const void* _p_void) -> std::shared_ptr<void> {
    return nullptr; }));
  m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::CREATE_PIPE_HANDLE), [&](const void* _p_void) -> std::shared_ptr<void> {
    return nullptr; }));
}


void CTempFunction_Client::init_selected_func(void)
{
  m_map_selected_func.emplace(std::make_pair(static_cast<size_t>(SELECTED_FUNC::PIPE_CLIENT), [&](const void* _p_void) -> std::shared_ptr<void> {
    auto shar_pipe_handle = m_map_func[static_cast<size_t>(FUNC::CREATE_PIPE_HANDLE)](nullptr);
    HANDLE& pipe_handle = *(HANDLE*)shar_pipe_handle.get();

    m_map_func[static_cast<size_t>(FUNC::CONNECT_PIPE)](&pipe_handle);

    return nullptr; }));
}


void CTempFunction_Client::render(void)
{
  auto shar_title = m_map_selected_func[static_cast<size_t>(COMMON_SELECTED_FUNC::PRINT_TITLE)](nullptr);
  CTempFunction::render(*(TString*)shar_title.get());
}

void CTempFunction_Client::render(const void* _p_void)
{
}

int CTempFunction_Client::update(int _event)
{
  m_map_selected_func[static_cast<size_t>(_event)](nullptr);
  return 0;
}

void CTempFunction_Client::release(void)
{
}
