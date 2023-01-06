#pragma once

#include "Headers.h"
#include "DEFINE_MGR.hpp"
#include "CTempFunction.h"

class CTempFunctionMgr
{
	DECLARE_SINGLETON(CTempFunctionMgr);
private:
	CTempFunctionMgr() : m_uniq_tempfunction(nullptr) { }

private:
	std::unique_ptr<CTempFunction> m_uniq_tempfunction;

public:
	void SetTempFunction(const int& _practice_num) noexcept;
	int Execute(std::function<void(void)> _func) {
		_func();
		return Execute();
	}
	int Execute();
};

