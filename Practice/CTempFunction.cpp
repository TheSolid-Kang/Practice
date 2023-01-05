#include "CTempFunction.h"


CTempFunction::CTempFunction()
{
	m_vec_func = std::vector<std::function<std::shared_ptr<void>(const void*)>>(static_cast<size_t>(COMMON_FUNC::END));
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
