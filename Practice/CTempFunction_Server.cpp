#include "CTempFunction_Server.h"
#define PIPE_NAME "\\\\.\\pipe\\YOATSFPipe"
#define BUF_SIZE 32768

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
  m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::ROOT), [&](const void* _p_void) -> std::shared_ptr<void> {
    return nullptr; }));
  m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::CREATE_PIPE_HANDLE), [&](const void* _p_void) -> std::shared_ptr<void> {
    std::cout << "확인" << std::endl;
    //0. 초기화
    HANDLE pipe_handle = NULL;


    char buf[BUF_SIZE] = { 0, };
    //1. 파이프 생성
    pipe_handle = ::CreateNamedPipeA(
      PIPE_NAME
      , PIPE_ACCESS_DUPLEX //양방향모드
      , PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT
      , PIPE_UNLIMITED_INSTANCES //최대 255개 인스턴스
      , BUF_SIZE //출력버퍼
      , BUF_SIZE //입력버퍼
      , NMPWAIT_USE_DEFAULT_WAIT //타입아웃
      , NULL);//보안속성

    //2. 파이프가 문제 없이  생성되었는지 확인
    if (pipe_handle == INVALID_HANDLE_VALUE)
    {
      printf("Pipe create failure!!\n");
      return NULL;
    }
    auto shar_pipe_handle = std::make_shared<HANDLE>(pipe_handle);
    return shar_pipe_handle; }));
  m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::CONNECT_PIPE), [&](const void* _p_void) -> std::shared_ptr<void> {
    auto pipe_handle = *(HANDLE*)_p_void;
    DWORD dword_nread = 0;
    DWORD dword_nwrite = 0;
    BOOL brtv = FALSE;
    char buf[BUF_SIZE] = { 0, };
    while (true)
    {
      // 이전에 연결된 파이프가 있는지 초기화한다.
      ::DisconnectNamedPipe(pipe_handle);

      //클라이언트가 연결되기를 기다린다.
      //클라이언트가 연결되기 전에는 리턴되지 않는다.
      BOOL is_connected = ConnectNamedPipe(pipe_handle, NULL); //0 == FALSE, 1 == TRUE
      auto last_error = ::GetLastError();
      // is_connected이 FALSE이고 GetLastError가 ERROR_PIPE_CONNECTED이면 정상 연결된 경우이므로 is_connected을 TRUE로 해준다.
      if (is_connected == FALSE && last_error == ERROR_PIPE_CONNECTED)
        is_connected = TRUE;

      //3. 정상 연결인 경우 서버 실행
      if (TRUE == is_connected) //파이프에 성공적으로 연결 되었다면 아래의 코드 실행
      {
        std::cout << "연결 성공 \n";
        brtv = ::ReadFile(pipe_handle, buf, BUF_SIZE, &dword_nread, NULL);
        std::cout << "읽기 == " << buf << std::endl;
        ::Sleep(100);
        // 버퍼에 있는것을 비운다.
        ::FlushFileBuffers(pipe_handle);


        brtv = ::WriteFile(pipe_handle, buf, BUF_SIZE, &dword_nwrite, NULL);
        std::cout << "작성 == " << buf << std::endl;
        ::Sleep(100);
        // 버퍼에 있는것을 비운다.
        ::FlushFileBuffers(pipe_handle);
      }
    }

    // 파이프를 닫아준다.
    ::CloseHandle(pipe_handle);
    return nullptr; }));
}


void CTempFunction_Server::init_selected_func(void)
{
  m_map_selected_func.emplace(std::make_pair(static_cast<size_t>(SELECTED_FUNC::PIPE_SERVER), [&](const void* _p_void) -> std::shared_ptr<void> {
    auto shar_pipe_handle = m_map_func[static_cast<size_t>(FUNC::CREATE_PIPE_HANDLE)](nullptr);
    HANDLE& pipe_handle = *(HANDLE*)shar_pipe_handle.get();

    m_map_func[static_cast<size_t>(FUNC::CONNECT_PIPE)](&pipe_handle);

    return nullptr; }));
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
  m_map_selected_func[static_cast<size_t>(_event)](nullptr);
  return 0;
}

void CTempFunction_Server::release(void)
{
}
