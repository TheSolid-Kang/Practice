#include "CTempFunction_Server.h"
#define PIPE_NAME "\\\\.\\pipe\\echo"
#define BUF_SIZE 32768

CTempFunction_Server::CTempFunction_Server()
{
}

CTempFunction_Server::~CTempFunction_Server()
{
}

void CTempFunction_Server::_Initialize(void)
{
	auto arr_title = _BuildArray(_T(" ")
		, _T("1. 파이프 서버 구현")
		, _T("2. ")
		, _T("")
		, _T("99. EXIT"));
	m_list_title.insert(m_list_title.end(), arr_title.begin(), arr_title.end());
	_InitFunc();
	_InitSelectedFunc();
}

void CTempFunction_Server::_InitFunc(void)
{
	m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::ROOT), [&](const void* _p_void) -> std::shared_ptr<void> {
		return nullptr; }));
#pragma region 파이프 서버 구현부
	m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::SET_PIPE_NAME), [&](const void* _p_void) -> std::shared_ptr<void> {
		TString exePath = CFileMgr::GetEXEFilePath();
		TString dirPath = exePath + _T("\\Server");
		TString settingIniPath = dirPath + _T("\\Setting.ini");
		//실행 경로에 Server 폴더가 없는 경우 Server 폴더 생성
		if (false == std::filesystem::is_directory(dirPath))
			CFileMgr::CreateDirectorys(dirPath);

		//Server 폴더에 Setting.ini가 없는 경우 Setting.ini파일 생성한 후 내용 채워넣음.
		if (false == std::filesystem::exists(settingIniPath))
			CINIMgr::WritePrivateProfileString_INI(_T("SET"), _T("PIPE_NAME"), _T("\\\\.\\pipe\\echo"), settingIniPath);
		m_PIPE_NAME = CINIMgr::GetPrivateProfileString_INI(_T("SET"), _T("PIPE_NAME"), settingIniPath);

		return nullptr; }));
	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::RESPOND_TEMP), [&](const void* _p_void) -> std::shared_ptr<void> {
		auto arr_response = _BuildArray("BENDINGCOUNT", "CUTTINGCOUNT", "STATUS", "WIRESTATE", "WIRELEN", "EQUIPMENT_NAME");
		auto shar_map_response = std::make_shared<std::map<std::string, std::string>>();
		for (auto _response : arr_response)
			(*shar_map_response)[_response] = "0";
		return shar_map_response; }));

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::INSPECT_PIPE_HANDLE), [&](const void* _p_void) -> std::shared_ptr<void> {
		auto pipe_handle = *(HANDLE*)_p_void;
		try {
			BOOL result;
			//GetNamedPipeClientComputerName = 1;
			LPSTR  ClientComputerName = { 0 };
			ULONG  ClientComputerNameLength = 1024;
			result = ::GetNamedPipeClientComputerNameA(pipe_handle, ClientComputerName, ClientComputerNameLength);
			//GetNamedPipeClientProcessId = 1;
			PULONG ClientProcessId = { 0 };
			result = ::GetNamedPipeClientProcessId(pipe_handle, ClientProcessId);

			//GetNamedPipeClientSessionId = 1;
			PULONG ClientSessionId = { 0 };
			result = ::GetNamedPipeClientSessionId(pipe_handle, ClientSessionId);

			//GetNamedPipeHandleState = 1;
			LPDWORD lpState = { 0 };
			LPDWORD lpCurInstances = { 0 };
			LPDWORD lpMaxCollectionCount = { 0 };
			LPDWORD lpCollectDataTimeout = { 0 };
			LPSTR   lpUserName = { 0 };
			DWORD   nMaxUserNameSize = { 0 };
			result = ::GetNamedPipeHandleStateA(pipe_handle, lpState, lpCurInstances, lpMaxCollectionCount, lpCollectDataTimeout, lpUserName, nMaxUserNameSize);

			//GetNamedPipeServerProcessId = 1;

			//GetNamedPipeServerSessionId = 1;

			//PeekNamedPipe = 1;

			//SetNamedPipeHandleState = 1;

			//TransactNamedPipe = 1;

			//WaitNamedPipe = 1;
		}
		catch (std::exception& _e) {
			std::cout << _e.what() << std::endl;
		}
		return nullptr; }));

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::CREATE_PIPE_HANDLE), [&](const void* _p_void) -> std::shared_ptr<void> {
		std::cout << "확인" << std::endl;
		//0. 초기화
		HANDLE pipe_handle = NULL;


		char buf[BUF_SIZE] = { 0, };
		//1. 파이프 생성
		pipe_handle = ::CreateNamedPipe(
			m_PIPE_NAME.c_str()
			, PIPE_ACCESS_DUPLEX //양방향모드
			, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT //message type pipe,  message-read mode, blocking mode
			, PIPE_UNLIMITED_INSTANCES //최대 255개 인스턴스
			, BUF_SIZE //출력버퍼
			, BUF_SIZE //입력버퍼
			, NMPWAIT_USE_DEFAULT_WAIT //타입아웃
			, NULL);//보안속성

		  //2. 파이프가 문제 없이  생성되었는지 확인
		if (pipe_handle == INVALID_HANDLE_VALUE)
		{
			printf("Pipe create failure!!\n");
			exit(0);//프로그램 종료 함수
			return NULL;
		}
		auto shar_pipe_handle = std::make_shared<HANDLE>(pipe_handle);
		return shar_pipe_handle; }));

	/// <summary>
	/// 
	/// 1. 변수 초기화
	/// 2. 파이프 클라이언트 연결 대기
	///   1) 클라이언트가 정상적으로 연결되었는지 확인
	///   2) 클라이언트가 정상적으로 연결되지 않았다면 프로그램 종료: exit(0);
	/// 3. 파이프 클라이언트가 정상적으로 연결되었으므로 데이터 통신 시작
	///   1) 클라이언트가 파이프 버퍼에 작성한 데이터를 읽고 buf(로컬 변수)에 저장한다.
	///   2) 파이프 버퍼에 있는 데이터를 비운다.
	///   3) buf(로컬 변수)에 담긴 데이터로 작업한다.
	///   4) 작업 결과를 파이프 버퍼에 '쓰기' 한다.
	///   5) 파이프 버퍼에 있는 데이터를 비운다.
	/// 4. 이전에 연결된 파이프 클라이언트의 핸들을 닫는다.
	/// 5. 파이프를 닫아준다.
	/// </summary>
	/// <param name=""></param>
	m_map_func.emplace(std::make_pair(static_cast<size_t>(FUNC::CONNECT_PIPE), [&](const void* _p_void) -> std::shared_ptr<void> {
		//1. 변수 초기화
		auto pipe_handle = *(HANDLE*)_p_void;
		DWORD dword_nread = 0;
		DWORD dword_nwrite = 0;
		BOOL brtv = FALSE;
		char buf[BUF_SIZE] = { 0, };

		auto shar_map_response = m_map_func[static_cast<size_t>(FUNC::RESPOND_TEMP)](nullptr);
		auto& r_map_response = *(std::map<std::string, std::string>*)shar_map_response.get();
		r_map_response["EQUIPMENT_NAME"] = "Second Server";//230111 임시 하드코딩

		while (true)
		{
			//2. 파이프 클라이언트 연결 대기
			//파이프 클라이언트가 연결되기를 기다린다.
			//클라이언트가 연결되기 전에는 리턴되지 않는다.
			BOOL is_connected = ConnectNamedPipe(pipe_handle, NULL); //0 == FALSE, 1 == TRUE
			//auto shar_map_response = m_map_func[static_cast<size_t>(FUNC::INSPECT_PIPE_HANDLE)](&pipe_handle);

			//  1) 클라이언트가 정상적으로 연결되었는지 확인
			auto last_error = ::GetLastError();
			//  2) 클라이언트가 정상적으로 연결되지 않았다면 프로그램 종료: exit(0);
			//ConnectNamedPipe가 FALSE이고 GetLastError가 ERROR_PIPE_CONNECTED이면 
			//망한 거임.
			if (is_connected == FALSE && last_error == ERROR_PIPE_CONNECTED)
				exit(0);//프로그램 종료 함수

			  //3. 파이프 클라이언트가 정상적으로 연결되었으므로 데이터 통신 시작
			std::cout << "연결 성공 \n";
			int i = 0;
			while (++i <= r_map_response.size())
			{
				//  1) 클라이언트가 파이프 버퍼에 작성한 데이터를 읽고 buf(로컬 변수)에 저장한다.
				brtv = ::ReadFile(pipe_handle, buf, BUF_SIZE, &dword_nread, NULL);//dword_nread == lpNumberOfBytesRead
				std::cout << "읽기 == " << buf << std::endl;
				//  2) 파이프 버퍼에 있는 데이터를 비운다.
				::FlushFileBuffers(pipe_handle);

				//  3) buf(로컬 변수)에 담긴 데이터로 작업한다.
				std::string key(buf);
				char temp_buf[BUF_SIZE] = { 0, };
				strcpy_s(buf, temp_buf);//buf를 비운다.
				strcpy_s(buf, const_cast<char*>(r_map_response[key].c_str()));

				//brtv = ::WriteFile(pipe_handle, buf, BUF_SIZE, &dword_nwrite, NULL); 
				//클라이언트가 받는 문자열의 최대치는 255였음, 
				//255를 '넘어가는 길이의 문자열'(길이: 32768)을 write해서 계속 멈춘 거임.

				//  4) 작업 결과를 파이프 버퍼에 '쓰기' 한다.
				brtv = ::WriteFile(pipe_handle, buf, strlen(buf) + 1, &dword_nwrite, NULL);
				std::cout << "작성 == " << buf << std::endl;
				//  5) 파이프 버퍼에 있는 데이터를 비운다.
				::FlushFileBuffers(pipe_handle);

			}
			//4. 이전에 연결된 파이프 클라이언트의 핸들을 닫는다.
			::DisconnectNamedPipe(pipe_handle);
		}

		//5. 파이프를 닫아준다.
		::CloseHandle(pipe_handle);
		return nullptr; }));
#pragma endregion
}


void CTempFunction_Server::_InitSelectedFunc(void)
{
	m_map_selected_func.emplace(std::make_pair(static_cast<size_t>(SELECTED_FUNC::PIPE_SERVER), [&](const void* _p_void) -> std::shared_ptr<void> {
		m_map_func[static_cast<size_t>(FUNC::SET_PIPE_NAME)](nullptr);
		auto shar_pipe_handle = m_map_func[static_cast<size_t>(FUNC::CREATE_PIPE_HANDLE)](nullptr);
		HANDLE& pipe_handle = *(HANDLE*)shar_pipe_handle.get();

		m_map_func[static_cast<size_t>(FUNC::CONNECT_PIPE)](&pipe_handle);

		return nullptr; }));
}


void CTempFunction_Server::_Render(void)
{
	auto shar_title = m_map_selected_func[static_cast<size_t>(COMMON_SELECTED_FUNC::PRINT_TITLE)](nullptr);
	CTempFunction::_Render(*(TString*)shar_title.get());
}

void CTempFunction_Server::_Render(const void* _p_void)
{
}

int CTempFunction_Server::_Update(int _event)
{
	m_map_selected_func[static_cast<size_t>(_event)](nullptr);
	return 0;
}

void CTempFunction_Server::_Release(void)
{
}
