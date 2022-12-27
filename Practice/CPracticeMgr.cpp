#include "CPracticeMgr.h"
#include "Enum.h"

#include "CPractice_1.h"
#include "CPractice_2.h"

IMPLEMENT_SINGLETON(CPracticeMgr);

void CPracticeMgr::SetPractice(const int& _practice_num) noexcept
{
	if (m_uniq_practice != nullptr)
		m_uniq_practice.reset();

	switch (_practice_num)
	{
	case static_cast<int>(PRACTICE_NUM::PN_1):
		m_uniq_practice = std::make_unique<CPractice_1>();
		break;
	case static_cast<int>(PRACTICE_NUM::PN_2):
		m_uniq_practice = std::make_unique<CPractice_2>();
		break;


	case static_cast<int>(PRACTICE_NUM::PNEND):
		break;
	}
}

int CPracticeMgr::Execute()
{
	return (*m_uniq_practice).execute();
}

