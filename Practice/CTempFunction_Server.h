#pragma once
#include "CTempFunction.h"
class CTempFunction_Server :
    public CTempFunction
{
public:
	CTempFunction_Server();
	~CTempFunction_Server();

private:
	// ITempFunction을(를) 통해 상속됨
	virtual void initialize(void) override;
	virtual void init_func(void) override;
	virtual void init_selected_func(void) override;
	virtual void render(void) override;
	virtual void render(const void* _p_void) override;
	virtual int update(int _event = 0) override;
	virtual void release(void) override;
};