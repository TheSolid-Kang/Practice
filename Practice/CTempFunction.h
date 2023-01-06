#pragma once
#include "Headers.h"

class ITempFunction {
protected:
	virtual void initialize() = 0;
	virtual void init_func() = 0;
	virtual void init_selected_func() = 0;
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

protected:
	enum class COMMON_FUNC : size_t { PRINT_TITLE, END};
	enum class COMMON_SELECTED_FUNC : size_t { PRINT_TITLE, END };
	enum class TEST : size_t;
	std::list<TString> m_list_title;
	std::map<size_t, std::function<std::shared_ptr<void>(const void*)>> m_map_func;
	std::map<size_t, std::function<std::shared_ptr<void>(const void*)>> m_map_selected_func;

protected:
	// ITempFunction을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void init_func() override;
	virtual void init_selected_func() override;
	void render(const TString& _str) override;
	virtual int render() override;
	virtual int update() override;
	virtual void release() override;

public:
	virtual int Execute() final;

protected:
	template<typename... Args>//분석 필요: 이해 없이 컴파일되기에 사용하는 코드.
	auto build_array(Args&&... _args)
		->std::array<std::common_type_t<Args...>, sizeof ...(_args)>
	{ return { std::forward < std::common_type_t<Args...>>((Args&&)_args)... }; }
};