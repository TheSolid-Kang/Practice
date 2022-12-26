#include "CPracticeMgr.h"
#include "Enum.h"


IMPLEMENT_SINGLETON(CPracticeMgr);

void CPracticeMgr::SetPractice(const int& _practice_num) noexcept
{
	if (m_uniq_practice != nullptr)
		m_uniq_practice.reset();

	switch (_practice_num)
	{
	case static_cast<int>(PRACTICE_NUM::PN221226):

		break;


	case static_cast<int>(PRACTICE_NUM::PNEND):
		break;
	}
}

int CPracticeMgr::Execute()
{
	return (*m_uniq_practice).execute();
}

