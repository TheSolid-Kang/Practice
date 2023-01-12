#include "CPractice_2.h"
#include "../MySQL_DAO_v2/MySQL_DAO_v2.hpp"
#include "../MySQL_DAO_v2/MySQL_DAO_v3.h"
#include <numeric> //accumulate 사용

#include "KMP.h"
#include <tuple>

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
		_T(" ")
		, _T("")
		, _T("99. EXIT") );
	m_list_title.insert(m_list_title.end(), arr_title.begin(), arr_title.end());
	init_func();
	init_selected_func();
}

void CPractice_2::render() 
{
	std::for_each(m_list_title.cbegin(), m_list_title.cend(), [&](const TString& _title) {std::tcout << _title << std::endl; });
}

void CPractice_2::render(const void* _p_void)
{
}

int CPractice_2::update(int _event)
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
	case static_cast<size_t>(TEST_FUNC::FIVE):
		(*m_uniq_map_testfunc)[static_cast<size_t>(TEST_FUNC::FIVE)](nullptr);
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

			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::FOUR)
		, [&](const void* _p_void) {


			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::FIVE)
		, [&](const void* _p_void) {
			
			return nullptr; }));
}

void CPractice_2::init_selected_func(void)
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
		, [&](const void* _p_void) {
			(*m_uniq_map_func)[static_cast<size_t>(FUNC::FIVE)](nullptr);
			return nullptr; }));


}


