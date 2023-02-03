#include "CForwardList.hpp"
#include "CPractice_1.h"
#include <forward_list>
CPractice_1::CPractice_1()
	: m_uniq_map_func(std::make_unique<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>>())
	, m_uniq_map_testfunc(std::make_unique<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>>())

{
}

CPractice_1::~CPractice_1()
{

}

void CPractice_1::_Initialize()
{
	auto arr_title = _BuildArray(_T(" ")
		, _T("1. foreard_list 예제")
		, _T("2. ForwardList 구현")
		, _T("")
		, _T("99. EXIT")
	);
	m_list_title.insert(m_list_title.end(), arr_title.begin(), arr_title.end());
	_InitFunc();
	_InitSelectedFunc();
}

void CPractice_1::_Render() 
{
	std::for_each(m_list_title.cbegin(), m_list_title.cend(), [&](const TString& _title) { std::tcout << _title << std::endl; });
}

void CPractice_1::_Render(const void* _p_void)
{
}

int CPractice_1::_Update(int _event)
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

void CPractice_1::_Release()
{

}

void CPractice_1::_InitFunc(void)
{
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::ONE),
		[&](const void* _p_void) -> std::shared_ptr<void> {
			std::forward_list<int> forwardList;
			forwardList.push_front(1);
			forwardList.push_front(0);
			forwardList.push_front(1);
			forwardList.push_front(1);
			forwardList.push_front(2);
			forwardList.push_front(2);
			forwardList.push_front(2);
			forwardList.push_front(2);
			forwardList.push_front(3);
			forwardList.push_front(3);
			forwardList.push_front(3);
			forwardList.push_front(1);

			forwardList.pop_front();

			forwardList.sort();

			forwardList.remove(1);
			forwardList.remove_if([](auto _first) -> bool { return _first >= 3 ? true : false; });

			auto iter = forwardList.begin();



			forwardList.clear();


			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::TWO),
		[&](const void* _p_void) -> std::shared_ptr<void> {
			CForwardList<int> forwardList;
			forwardList.push_front(1);
			forwardList.push_front(0);
			forwardList.push_front(1);
			forwardList.push_front(1);
			forwardList.push_front(2);
			forwardList.push_front(2);
			forwardList.push_front(3);
			forwardList.push_front(2);
			forwardList.push_front(2);
			forwardList.push_front(3);
			forwardList.push_front(2);
			forwardList.push_front(3);
			forwardList.push_front(1);
			auto num = forwardList.pop_front();
			const auto num2 = forwardList.pop_front();
			forwardList.push_front(forwardList.pop_front());

			forwardList.sort();

			forwardList.remove(1);
			forwardList.remove_if([](auto _first) -> bool { return _first >= 3 ? true : false; });


			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::THREE),
		[&](const void* _p_void) -> std::shared_ptr<void> {
			auto path = CFileMgr::GetOpenFolderDialg(_T("C:\\"));
			auto vec_file_name = CFIOMgr::GetRecursiveFilesInDirectory(path);
			for (auto _file_name : vec_file_name)
			{
				TCHAR* path = const_cast<TCHAR*>(_file_name.c_str());
				std::tcout << CFileMgr::GetFileType(path) << std::endl;
			}
			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::FOUR),
		[&](const void* _p_void) -> std::shared_ptr<void> {
			auto vec_file_name = CFileMgr::getTxtFiles(_T("C:\\Caleb\\CalebRecord"));
			for (auto _file_name : vec_file_name)
			{
				TCHAR* path = const_cast<TCHAR*>(_file_name.c_str());
				std::tcout << CFileMgr::GetFileType(path) << std::endl;
			}

			return nullptr; }));
	(*m_uniq_map_func).emplace(std::make_pair(static_cast<size_t>(FUNC::FIVE),
		[&](const void* _p_void) -> std::shared_ptr<void> {

			return nullptr; }));
}

void CPractice_1::_InitSelectedFunc(void)
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
