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
	_Initialize();
	_Render();
	int result = _Update();

	_Release();
	auto memory_info = _CrtDumpMemoryLeaks();
	std::tcout << _T("Memory: ") << memory_info << std::endl;
	return result;
}

void CPractice::_Initialize(void)
{
}

void CPractice::_InitFunc(void)
{
}

void CPractice::_InitSelectedFunc(void)
{
}

void CPractice::_Render(void)
{
}

void CPractice::_Render(const void* _p_void)
{
}

void CPractice::_Render(TString& _str)
{
	std::tcout << _str << std::endl;
}

int CPractice::_Update(int _event)
{
	return 0;
}

void CPractice::_Release(void)
{
}
