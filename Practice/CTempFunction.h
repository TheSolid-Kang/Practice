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

protected:
	enum class COMMON_FUNC : size_t { PRINT_TITLE, END};
	enum class COMMON_SELECTED_FUNC : size_t { PRINT_TITLE, END };
	enum class TEST : size_t;
	std::list<TString> m_list_title;
	std::vector<std::function<std::shared_ptr<void>(const void*)>> m_vec_func;
	std::vector<std::function<std::shared_ptr<void>(const void*)>> m_vec_selected_func;

protected:
	// ITempFunction을(를) 통해 상속됨
	virtual void initialize() override;
	void render(const TString& _str) override;
	virtual int render() override;
	virtual int update() override;
	virtual void release() override;

};