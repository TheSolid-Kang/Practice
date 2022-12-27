#include "CPractice_1.h"

CPractice_1::CPractice_1()
	: m_uniq_map_func(std::make_unique<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>>())
	, m_uniq_map_testfunc(std::make_unique<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>>())

{
}

CPractice_1::~CPractice_1()
{

}

void CPractice_1::initialize()
{
	auto arr_title = build_array(_T("1. CFIO 테스트")
		, _T("2. CFileMgr 테스트")
		, _T("3. baekjoon 폴더 내 파일 출력")
		, _T("4. baekjoon 폴더 내 파일출력: recursive(폴더를 제외한 모든 파일 출력)")
		, _T("")
		, _T("")
		, _T("99. EXIT")
	);
	m_list_title.insert(m_list_title.end(), arr_title.begin(), arr_title.end());
	init_func();
	init_testfunc();
}

void CPractice_1::render() noexcept
{
	std::for_each(m_list_title.cbegin(), m_list_title.cend(), [&](const TString& _title) { std::tcout << _title << std::endl; });
}

int CPractice_1::update()
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

void CPractice_1::release()
{

}

void CPractice_1::init_func(void)
{
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::ONE),
		[&](const void* _p_void) -> std::shared_ptr<void> {
			auto exe_dir_path = CFIOMgr::GetEXEFilePath();
			std::tcout << exe_dir_path << std::endl;
			return nullptr; 
		}));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::TWO),
		[&](const void* _p_void) -> std::shared_ptr<void> {
			auto baekjoon_dir_path = CFIOMgr::GetEXEFilePath() + _T("\\baekjoon\\step_1\\25083.txt");
			CFileMgr::ExecuteFile(baekjoon_dir_path);
			return nullptr; 
		}));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::THREE),
		[&](const void* _p_void) -> std::shared_ptr<void> {
			auto baekjoon_dir_path = CFIOMgr::GetEXEFilePath() + _T("\\baekjoon\\");
			auto vec_file = CFIOMgr::GetFilesInDirectory( baekjoon_dir_path);
			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::FOUR),
		[&](const void* _p_void) -> std::shared_ptr<void> {
			auto baekjoon_dir_path = CFIOMgr::GetEXEFilePath() + BAEKJOON_DIR_PATH;
			auto vec_file = CFIOMgr::GetRecursiveFilesInDirectory(baekjoon_dir_path);
			std::for_each(vec_file.cbegin(), vec_file.cend(), [](const TString& _file_path) {std::tcout << _file_path << std::endl; });
			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::FIVE),
		[&](const void* _p_void) -> std::shared_ptr<void> {return nullptr; }));
}

void CPractice_1::init_testfunc(void)
{
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::ONE),
		[&](const void* _p_void) -> std::shared_ptr<void> {
			(*m_uniq_map_func)[static_cast<size_t>(FUNC::ONE)](nullptr);
			return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::TWO),
		[&](const void* _p_void) -> std::shared_ptr<void> {
			(*m_uniq_map_func)[static_cast<size_t>(FUNC::TWO)](nullptr);
			return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::THREE),
		[&](const void* _p_void) -> std::shared_ptr<void> {
			(*m_uniq_map_func)[static_cast<size_t>(FUNC::THREE)](nullptr);
			return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::FOUR),
		[&](const void* _p_void) -> std::shared_ptr<void> {			
			(*m_uniq_map_func)[static_cast<size_t>(FUNC::FOUR)](nullptr);
			return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::FIVE),
		[&](const void* _p_void) -> std::shared_ptr<void> {return nullptr; }));
}
