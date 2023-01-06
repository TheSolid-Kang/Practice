#include "CTempFunctionMgr.h"
#include "Enum.h"

IMPLEMENT_SINGLETON(CTempFunctionMgr);

void CTempFunctionMgr::SetTempFunction(const int& _practice_num) noexcept
{
	if (m_uniq_tempfunction != nullptr)
		m_uniq_tempfunction.reset();

	switch (_practice_num)
	{
	case static_cast<int>(TEMP_FUNC_NUM::TFN_1):
		m_uniq_tempfunction = std::make_unique<CTempFunction>();
		break;

	case static_cast<int>(TEMP_FUNC_NUM::END):
		break;
	}
}

int CTempFunctionMgr::Execute()
{
	return (*m_uniq_tempfunction).Execute();
}

