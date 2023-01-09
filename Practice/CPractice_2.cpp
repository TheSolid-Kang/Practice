#include "CPractice_2.h"
//#include "../MySQL_DAO_v2/MySQL_DAO_v2.hpp"
#include <numeric> //accumulate 사용

#include "KMP.h"


CPractice_2::CPractice_2()
	: m_uniq_map_func(std::make_unique<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>>())
	, m_uniq_map_testfunc(std::make_unique<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>>())
{

}

CPractice_2::~CPractice_2()
{
}

void CPractice_2::initialize()
{
	auto arr_title = build_array(
		_T("1. MySQL DB 연결 확인")
		, _T("2. 전체 Caleb 읽기, accumulate 사용 실해")
		, _T("3. 전체 Caleb 읽기")
		, _T("4. 파일 확인")
		, _T("")
		, _T("")
		, _T("99. EXIT") );
	m_list_title.insert(m_list_title.end(), arr_title.begin(), arr_title.end());
	init_func();
	init_testfunc();
}

void CPractice_2::render() noexcept
{
	std::for_each(m_list_title.cbegin(), m_list_title.cend(), [&](const TString& _title) {std::tcout << _title << std::endl; });
}

int CPractice_2::update()
{
	switch (CIO::ask_and_return_integer())
	{
	case static_cast<size_t>(TEST_FUNC::ONE):
		(*m_uniq_map_testfunc)[static_cast<size_t>(TEST_FUNC::ONE)](nullptr);
		break;
	case static_cast<size_t>(TEST_FUNC::TWO):
		(*m_uniq_map_testfunc)[static_cast<size_t>(TEST_FUNC::TWO)](nullptr);
		break;
	case static_cast<size_t>(TEST_FUNC::THREE):
		(*m_uniq_map_testfunc)[static_cast<size_t>(TEST_FUNC::THREE)](nullptr);
		break;
	case static_cast<size_t>(TEST_FUNC::FOUR):
		(*m_uniq_map_testfunc)[static_cast<size_t>(TEST_FUNC::FOUR)](nullptr);
		break;

	default:
		break;
	}

	return 0;
}

void CPractice_2::release()
{
}

void CPractice_2::init_func(void)
{
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::ONE)
		, [&](const void* _p_void) {
			//auto uniq_ResultSet = MySQL_DAO_v2::GetInstance().GetResultSet(_T("SELECT * FROM test"));
			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::TWO)
		, [&](const void* _p_void) {
			TString caleb_root_path = _T("C:\\Caleb\\CalebRecord");
			auto vec_caleb_path = CFIOMgr::GetFilesInDirectory(caleb_root_path);
			for (const TString& _caleb_path : vec_caleb_path)
			{
				auto vec_line = CFIOMgr::GetVecFileLines(_caleb_path);

				auto item = std::accumulate(vec_line.begin(), vec_line.end(), const_cast<TCHAR*>(_T(""))
					, [](TCHAR* _p_ch, TString& _p) {
						TString str(_p_ch);
						str += _p;
						_p_ch = &(*const_cast<TCHAR*>(str.c_str()));
						return _p_ch;
					});
			}

			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::THREE)
		, [&](const void* _p_void) {

			//0. 변수 초기화
			//TString caleb_root_path = CFileMgr::GetOpenFolderDialg(); //잘 됨.
			TString caleb_root_path = _T("C:\\Caleb\\CalebRecord");
			//  vector 컨테이너에 CalebRecord에 담긴 파일 path 입력
			auto vec_caleb_path = CFIOMgr::GetFilesInDirectory(caleb_root_path);
			std::map<TString, std::map<TString, int>> map_cnt;

			//1. 검색어 설정
			//auto search_key = CIO::ask_and_return_string(); //잘 안 됨.
			std::list<TString> list_search_key;
			list_search_key.emplace_back(_T("하나님"));
			list_search_key.emplace_back(_T("아버지"));
			list_search_key.emplace_back(_T("주님"));
			list_search_key.emplace_back(_T("태경"));
			list_search_key.emplace_back(_T("사랑"));

			//2. Caleb 내에서 검색 횟수 확인
			//  1) 컨테이너에서 caleb_path 선택
			for (const TString& _caleb_path : vec_caleb_path)
			{
				//  2) caleb.txt 파일에 담긴 모든 내용 입력
				TString caleb = CFIOMgr::GetFileLines(_caleb_path);
				for (TString _search_key : list_search_key)
				{
					//  3) 한 Caleb에서 검색어 별 언급횟수 확인 및 입력
					auto uniq_vec_address = KMP::GetSearchedAddress(caleb, _search_key);
					if ((*uniq_vec_address).size() != 0)
						map_cnt[_caleb_path][_search_key] += (*uniq_vec_address).size();
				}
			}
			//3. Console창에 각각의 Caleb에서 검색어 별 언급횟수 출력
			for (std::pair<TString, std::map<TString, int>> _pair_cnt : map_cnt)
			{
				std::tcout << _T("=====") << _pair_cnt.first << _T("=====") << std::endl;
				for (std::pair<TString, int> _pair : _pair_cnt.second)
					std::tcout << _T("    ") << _pair.first << _T(" == ") << _pair.second << std::endl;
			}



			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::FOUR)
		, [&](const void* _p_void) {
			//0. 확인 할 폴더 설정
			auto path = CFileMgr::GetOpenFolderDialg(_T("C:\\Users\\hoppi\\Desktop\\TheSolid_KANG\\Work\\ZVIEW\\정리 된 Raw File 목록\\영상처리 Param 별 구분\\"));

			//1. 폴더 내 들어있는 모든 파일들의 경로 컨테이너에 담기
			auto vec_file_name = CFIOMgr::GetRecursiveFilesInDirectory(path);
			std::map<TString, std::list<TString>> chmap_name;
			//2. 
			for (auto _file_path : vec_file_name)
			{
				size_t folder_index = _file_path.find_last_of(_T("\\/"));
				size_t file_name_size = _file_path.length() - folder_index;
				auto folder_path = _file_path.substr(0, folder_index);
				auto file_name = _file_path.substr(folder_index, file_name_size);
				chmap_name[file_name].emplace_back(folder_path);
			}


			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::FIVE)
		, [&](const void* _p_void) {
			
			return nullptr; }));
}

void CPractice_2::init_testfunc(void)
{
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::ONE)
		, [&](const void* _p_void) {return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::TWO)
		, [&](const void* _p_void) {
			(*m_uniq_map_func)[static_cast<size_t>(FUNC::TWO)](nullptr);
			return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::THREE)
		, [&](const void* _p_void) {
			(*m_uniq_map_func)[static_cast<size_t>(FUNC::THREE)](nullptr);
	return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::FOUR)
		, [&](const void* _p_void) {
			(*m_uniq_map_func)[static_cast<size_t>(FUNC::FOUR)](nullptr);
			return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::FIVE)
		, [&](const void* _p_void) {return nullptr; }));

}
