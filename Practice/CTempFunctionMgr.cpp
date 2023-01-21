#include "CTempFunctionMgr.h"
#include "Enum.h"

#include "CTempFunction_File.h"
#include "CTempFunction_CodingTest.h"
#include "CTempFunction_Server.h"
#include "CTempFunction_Client.h"

IMPLEMENT_SINGLETON(CTempFunctionMgr);

void CTempFunctionMgr::SetTempFunction(const int& _practice_num) noexcept
{
	if (m_uniq_tempfunction != nullptr)
		m_uniq_tempfunction.reset();

	switch (_practice_num)
	{
	case static_cast<int>(TEMP_FUNC_NUM::FILE):
		m_uniq_tempfunction = std::make_unique<CTempFunction_File>();
		break;
	case static_cast<int>(TEMP_FUNC_NUM::CODING_TEST):
		m_uniq_tempfunction = std::make_unique<CTempFunction_CodingTest>();
		break;
	case static_cast<int>(TEMP_FUNC_NUM::SERVER):
		m_uniq_tempfunction = std::make_unique<CTempFunction_Server>();
		break;
	case static_cast<int>(TEMP_FUNC_NUM::CLIENT):
		m_uniq_tempfunction = std::make_unique<CTempFunction_Client>();
		break;

	case static_cast<int>(TEMP_FUNC_NUM::END):
		break;
	}
}

int CTempFunctionMgr::Execute()
{
	return (*m_uniq_tempfunction).Execute();
}

