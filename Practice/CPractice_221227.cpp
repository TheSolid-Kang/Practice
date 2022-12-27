#include "CPractice_221227.h"

CPractice_221227::CPractice_221227()
	: m_uniq_map_func(std::make_unique<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>>())
	, m_uniq_map_testfunc(std::make_unique<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>>())
{
}

CPractice_221227::~CPractice_221227()
{
}

void CPractice_221227::initialize()
{
	auto arr_title = build_array(
		_T("1. ")
		, _T("")
		, _T("")
		, _T("99. EXIT") );
}

void CPractice_221227::render() noexcept
{
}

int CPractice_221227::update()
{
	return 0;
}

void CPractice_221227::release()
{
}

void CPractice_221227::init_func(void)
{
}

void CPractice_221227::init_testfunc(void)
{
}
