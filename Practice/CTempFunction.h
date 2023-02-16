#pragma once
#include "Headers.h"

class ITempFunction {
protected:
	virtual void _Initialize(void) = 0;
	virtual void _InitFunc(void) = 0;
	virtual void _InitSelectedFunc(void) = 0;
	virtual void _Render(void) = 0;
	virtual void _Render(const void* _p_void) = 0;
	virtual void _Render(TString _str) = 0;
	virtual int _Update(int _event = 0) = 0;
	virtual void _Release(void) = 0;
};

class CTempFunction : public ITempFunction
{
public:
	CTempFunction();
	~CTempFunction();

protected:
	enum class COMMON_FUNC : size_t { PRINT_TITLE, END};
	enum class TEST : size_t;
	std::list<TString> m_list_title;
	std::map<size_t, std::function<std::shared_ptr<void>(const void*)>> m_map_func;

public:
	enum class COMMON_SELECTED_FUNC : size_t { PRINT_TITLE, END };
	std::map<size_t, std::function<std::shared_ptr<void>(const void*)>> m_map_selected_func;

protected:
	// ITempFunction을(를) 통해 상속됨
	virtual void _Initialize(void) override;
	virtual void _InitFunc(void) override;
	virtual void _InitSelectedFunc(void) override;
	virtual void _Render(void) override;
	virtual void _Render(const void* _p_void) override;
	virtual void _Render(TString _str) override;
	virtual int _Update(int _event = 0) override;
	virtual void _Release(void) override;

public:
	virtual int Execute() final;

protected:
	template<typename... Args>//분석 필요: 이해 없이 컴파일되기에 사용하는 코드.
	auto _BuildArray(Args&&... _args)
		->std::array<std::common_type_t<Args...>, sizeof ...(_args)>
	{ return { std::forward < std::common_type_t<Args...>>((Args&&)_args)... }; }


};