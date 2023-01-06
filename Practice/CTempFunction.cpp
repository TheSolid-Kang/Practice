#include "CTempFunction.h"
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

}

void CTempFunction::init_selected_func(void)
{

}

void CTempFunction::render(const TString& _str)
{
	std::tcout << _str << std::endl;
}

int CTempFunction::render()
{
	return 0;
}

int CTempFunction::update()
{
	return 0;
}

void CTempFunction::release()
{
}

int CTempFunction::Execute()
{
	system("pause");
	system("cls");
	initialize();
	render();
	int result = update();

	release();
	auto memory_info = _CrtDumpMemoryLeaks();
	std::tcout << _T("Memory: ") << memory_info << std::endl;
	return result;
}