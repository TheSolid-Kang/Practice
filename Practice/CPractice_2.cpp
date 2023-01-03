#include "CPractice_2.h"
#include "../MySQL_DAO_v2/MySQL_DAO_v2.hpp"
CPractice_2::CPractice_2()
	: m_uniq_map_func(std::make_unique<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>>())
	, m_uniq_map_testfunc(std::make_unique<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>>())
{
	auto uniq_ResultSet = MySQL_DAO_v2::GetInstance().GetResultSet(_T("SELECT * FROM test"));

}

CPractice_2::~CPractice_2()
{
}

void CPractice_2::initialize()
{
	auto arr_title = build_array(
		_T("1. MySQL DB 연결 확인")
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
			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::TWO)
		, [&](const void* _p_void) {return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::THREE)
		, [&](const void* _p_void) {return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::FOUR)
		, [&](const void* _p_void) {return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::FIVE)
		, [&](const void* _p_void) {return nullptr; }));
}

void CPractice_2::init_testfunc(void)
{
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::ONE)
		, [&](const void* _p_void) {return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::TWO)
		, [&](const void* _p_void) {return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::THREE)
		, [&](const void* _p_void) {return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::FOUR)
		, [&](const void* _p_void) {return nullptr; }));
	(*m_uniq_map_testfunc).emplace(std::make_pair(static_cast<size_t>(TEST_FUNC::FIVE)
		, [&](const void* _p_void) {return nullptr; }));

}
