#include "CTempFunction.h"


CTempFunction::CTempFunction()
{
}

CTempFunction::~CTempFunction()
{
}

void CTempFunction::initialize()
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
