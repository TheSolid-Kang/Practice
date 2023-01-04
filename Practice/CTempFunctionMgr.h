#pragma once

#include "Headers.h"
#include "DEFINE_MGR.hpp"
#include "CTempFunction.h"

class CTempFunctionMgr
{
public:
	CTempFunctionMgr();
	~CTempFunctionMgr();
	DECLARE_SINGLETON(CTempFunctionMgr);
};

