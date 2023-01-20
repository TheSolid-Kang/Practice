#pragma once
#include "CPractice.h"
class CPractice_1 :public CPractice
{
public:
	CPractice_1();
	~CPractice_1();

private:
	enum class FUNC : size_t {ONE = 1, TWO, THREE, FOUR, FIVE};
	enum class TEST_FUNC : size_t {ONE = 1, TWO, THREE, FOUR, FIVE};
	std::unique_ptr<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>> m_uniq_map_func;
	std::unique_ptr<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>> m_uniq_map_testfunc;

private:
	virtual void initialize(void) override;
	virtual void init_func(void) override;
	virtual void init_selected_func(void) override;
	virtual void render(void) override;
	virtual void render(const void* _p_void) override;
	virtual int update(int _event = 0) override;
	virtual void release(void) override;


protected:
	template<typename... Args>
	auto build_array(Args&&... _args)
		-> std::array<std::common_type_t<Args...>, sizeof ...(_args)>
	{ return { std::forward<std::common_type_t<Args...>>((Args&&)_args)... }; }

private://230120_TEST
	void _Test(TCHAR* pch){ std::tcout << pch << std::endl; }

};

