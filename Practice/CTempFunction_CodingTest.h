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
	virtual void initialize() override;
	virtual void init_func() override;
	virtual void init_selected_func() override;
	virtual int render() override;
	virtual int update() override;
	virtual void release() override;
};

