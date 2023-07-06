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
	virtual void _Initialize(void) override;
	virtual void _InitFunc(void) override;
	virtual void _InitSelectedFunc(void) override;
	virtual void _Render(void) override;
	virtual void _Render(const void* _p_void) override;
	virtual int _Update(int _event = 0) override;
	virtual void _Release(void) override;
};

