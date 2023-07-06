#pragma once
#include "Headers.h"
#include "DEFINE_MGR.hpp"
#include "CPractice.h"

class CPracticeMgr
{
	DECLARE_SINGLETON(CPracticeMgr);
private:
	CPracticeMgr() : m_uniq_practice(nullptr) { }

private:
	std::unique_ptr<CPractice> m_uniq_practice;

public:
	void SetPractice(const int& _practice_num) noexcept;
	int Execute(std::function<void(void)> _func) {
		_func();
		return Execute();
	}
	int Execute();


};

