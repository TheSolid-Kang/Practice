#include "CTempFunction.h"
#include <crtdbg.h>
#if _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

CTempFunction::CTempFunction()
{
	(*this).initialize();
}

CTempFunction::~CTempFunction()
{
}

void CTempFunction::initialize()
{
	(*this).init_func();
	(*this).init_selected_func();
}

void CTempFunction::init_func(void)
{
	m_map_func.emplace(std::make_pair(static_cast<size_t>(COMMON_FUNC::PRINT_TITLE), [&](const void* _p_void) -> std::shared_ptr<void> {
		StringBuilder str_buil;
		std::for_each(m_list_title.cbegin(), m_list_title.cend(), [&str_buil](const TString& _ch_page) { str_buil.append_endl(_ch_page); });
		TString title = str_buil.str();
		auto shar_title = std::make_shared<TString>(title);
		return shar_title;
		}));
}

void CTempFunction::init_selected_func(void)
{
	m_map_selected_func.emplace(std::make_pair(static_cast<size_t>(COMMON_SELECTED_FUNC::PRINT_TITLE), [&](const void* _p_void) -> std::shared_ptr<void> {
		return m_map_func[static_cast<size_t>(COMMON_FUNC::PRINT_TITLE)](nullptr);
		}));
}

void CTempFunction::render(void)
{
}

void CTempFunction::render(const void* _p_void)
{
}

void CTempFunction::render(TString& _str)
{
	std::tcout << _str << std::endl;
}

int CTempFunction::update(int _event )
{
	return 0;
}

void CTempFunction::release(void)
{
}


int CTempFunction::Execute()
{
	system("pause");
	system("cls");
	initialize();
	render();
	int result = 0;
	int selected_func = CIO::ask_and_return_integer();
	if (selected_func > static_cast<int>(COMMON_SELECTED_FUNC::PRINT_TITLE) && selected_func < m_map_selected_func.size())
		result = update(selected_func);

	release();
	auto memory_info = _CrtDumpMemoryLeaks();
	std::tcout << _T("Memory: ") << memory_info << std::endl;
	return result;
}

