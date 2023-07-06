#pragma once
#include "CTempFunction.h"
class CTempFunction_Client :
	public CTempFunction
{
public:
	CTempFunction_Client();
	~CTempFunction_Client();
private:
	enum class FUNC : size_t {
		ROOT = static_cast<size_t>(COMMON_FUNC::END)
		//1. 파이프 서버
		, RESPOND_TEMP
		, INSPECT_PIPE_HANDLE
		, CREATE_PIPE_HANDLE
		, CONNECT_PIPE


		//2. 
		, END
	};
	enum class SELECTED_FUNC : size_t {
		PIPE_CLIENT = static_cast<size_t>(COMMON_SELECTED_FUNC::END)
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

