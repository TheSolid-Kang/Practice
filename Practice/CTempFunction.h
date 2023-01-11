#pragma once
#include "Headers.h"

class ITempFunction {
protected:
	virtual void initialize(void) = 0;
	virtual void init_func(void) = 0;
	virtual void init_selected_func(void) = 0;
	virtual void render(void) = 0;
	virtual void render(const void* _p_void) = 0;
	virtual void render(TString& _str) = 0;
	virtual int update(int _event = 0) = 0;
	virtual void release(void) = 0;
};

class CTempFunction : public ITempFunction
{
public:
	CTempFunction();
	~CTempFunction();

protected:
	enum class COMMON_FUNC : size_t { PRINT_TITLE, END};
	enum class COMMON_SELECTED_FUNC : size_t { PRINT_TITLE, END };
	enum class TEST : size_t;
	std::list<TString> m_list_title;
	std::map<size_t, std::function<std::shared_ptr<void>(const void*)>> m_map_func;
	std::map<size_t, std::function<std::shared_ptr<void>(const void*)>> m_map_selected_func;

protected:
	// ITempFunction을(를) 통해 상속됨
	virtual void initialize(void) override;
	virtual void init_func(void) override;
	virtual void init_selected_func(void) override;
	virtual void render(void) override;
	virtual void render(const void* _p_void) override;
	virtual void render(TString& _str) override;
	virtual int update(int _event = 0) override;
	virtual void release(void) override;

public:
	virtual int Execute() final;

protected:
	template<typename... Args>//분석 필요: 이해 없이 컴파일되기에 사용하는 코드.
	auto build_array(Args&&... _args)
		->std::array<std::common_type_t<Args...>, sizeof ...(_args)>
	{ return { std::forward < std::common_type_t<Args...>>((Args&&)_args)... }; }


};