#pragma once
#include "Headers.h"

class ITempFunction {
protected:
	virtual void initialize() = 0;
	virtual void render(const TString& _str) = 0;
	virtual int render() = 0;
	virtual int update() = 0;
	virtual void release() = 0;
};

class CTempFunction : public ITempFunction
{
public:
	CTempFunction();
	~CTempFunction();



	// ITempFunction을(를) 통해 상속됨
	virtual void initialize() override;
	void render(const TString& _str) override;
	virtual int render() override;
	virtual int update() override;
	virtual void release() override;

};