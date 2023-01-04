#pragma once
#include "CTempFunction.h"
class CTempFunction_File : public CTempFunction
{
public:
	CTempFunction_File();
	~CTempFunction_File();

	// ITempFunction을(를) 통해 상속됨
	virtual void initialize() override;
	virtual int render() override;
	virtual int update() override;
	virtual void release() override;
};

