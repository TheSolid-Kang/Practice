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
    , _T("1. 파이프 클라이언트")
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
    auto arr_response = build_array("BENDINGCOUNT", "CUTTINGCOUNT", "STATUS", "WIRESTATE", "WIRELEN", "EQUIPMENT_NAME");
    auto shar_map_response = std::make_shared<std::map<std::string, std::string>>();
    for (auto _response : arr_response)
      (*shar_map_response)[_response] = "0";
    return shar_map_response; }));
  m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::INSPECT_PIPE_HANDLE), [&](const void* _p_void) -> std::shared_ptr<void> {
    return nullptr; }));
  m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::CREATE_PIPE_HANDLE), [&](const void* _p_void) -> std::shared_ptr<void> {
    HANDLE pipe_handle = { 0 };
    BOOL is_created_pipe = ::WaitNamedPipeA(PIPE_NAME, NMPWAIT_WAIT_FOREVER);
    pipe_handle = ::CreateFileA(
      PIPE_NAME, GENERIC_READ | GENERIC_WRITE, 0
      , NULL, OPEN_EXISTING, 0, NULL);

    //2. 파이프가 문제 없이  생성되었는지 확인
    if (pipe_handle == INVALID_HANDLE_VALUE)
    {
      printf("Pipe create failure!!\n");
      exit(0);//프로그램 종료 함수
      return NULL;
    }

    auto shar_pipe_handle = std::make_shared<HANDLE>(pipe_handle);
    return shar_pipe_handle; }));
  m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::CONNECT_PIPE), [&](const void* _p_void) -> std::shared_ptr<void> {
    //auto pipe_handle = *(HANDLE*)_p_void;
    HANDLE pipe_handle = {0};
    DWORD dword_nread = 0;
    DWORD dword_nwrite = 0;
    BOOL brtv = FALSE;
    char buf[BUF_SIZE] = { 0, };

    auto shar_map_response = m_map_func[static_cast<size_t>(FUNC::RESPOND_TEMP)](nullptr);
    auto& r_map_response = *(std::map<std::string, std::string>*)shar_map_response.get();

    while (true)
    {
      auto shar_pipe_handle = m_map_func[static_cast<size_t>(FUNC::CREATE_PIPE_HANDLE)](nullptr);
      pipe_handle = *(HANDLE*)shar_pipe_handle.get();


      //3. 파이프 클라이언트가 정상적으로 연결되었으므로 데이터 통신 시작
      std::cout << "연결 성공 \n";
      int i = 0;
      while (++i <= r_map_response.size())
      {
        std::string msg = "  ";
        ::WriteFile(pipe_handle, msg.c_str(), strlen(msg.c_str()), &dword_nwrite, NULL);
        std::cout << "작성 == " << msg << std::endl;
        memset(buf, 0x00, BUF_SIZE);
        ::FlushFileBuffers(pipe_handle);

        brtv = ::ReadFile(pipe_handle, buf, BUF_SIZE, &dword_nread, NULL);
        std::cout << "읽기 == " << buf << std::endl;
        memset(buf, 0x00, BUF_SIZE);
        ::FlushFileBuffers(pipe_handle);
      }
    }

    ::CloseHandle(pipe_handle);
    return nullptr; }));

}


void CTempFunction_Client::init_selected_func(void)
{
  m_map_selected_func.emplace(std::make_pair(static_cast<size_t>(SELECTED_FUNC::PIPE_CLIENT), [&](const void* _p_void) -> std::shared_ptr<void> {
    //auto shar_pipe_handle = m_map_func[static_cast<size_t>(FUNC::CREATE_PIPE_HANDLE)](nullptr);
    //HANDLE& pipe_handle = *(HANDLE*)shar_pipe_handle.get();

    //m_map_func[static_cast<size_t>(FUNC::CONNECT_PIPE)](&pipe_handle);
    m_map_func[static_cast<size_t>(FUNC::CONNECT_PIPE)](nullptr);

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
