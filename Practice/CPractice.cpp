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

int CPractice::execute()
{
	system("pause");
	system("cls");
	initialize();
	render();
	int result = update();

	release();
	auto memory_info = _CrtDumpMemoryLeaks();
	std::tcout << _T("메모리: ") << memory_info << std::endl;
	return result;
}
