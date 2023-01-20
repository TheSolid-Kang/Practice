#include "CPractice.h"

#if _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

CPractice::CPractice()
{

}

CPractice::~CPractice()
{
}

int CPractice::Execute()
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

void CPractice::initialize(void)
{
}

void CPractice::init_func(void)
{
}

void CPractice::init_selected_func(void)
{
}

void CPractice::render(void)
{
}

void CPractice::render(const void* _p_void)
{
}

void CPractice::render(TString& _str)
{
	std::tcout << _str << std::endl;
}

int CPractice::update(int _event)
{
	return 0;
}

void CPractice::release(void)
{
}
