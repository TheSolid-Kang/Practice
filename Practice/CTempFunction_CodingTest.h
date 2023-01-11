#pragma once
#include "CTempFunction.h"
class CTempFunction_CodingTest :
    public CTempFunction
{
public:
	CTempFunction_CodingTest();
	~CTempFunction_CodingTest();

private:
	enum class FUNC : size_t {
		ROOT = static_cast<size_t>(COMMON_FUNC::END)
		, END
	};
	enum class SELECTED_FUNC : size_t {
		ROOT = static_cast<size_t>(COMMON_SELECTED_FUNC::END)
		, END
	};
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

