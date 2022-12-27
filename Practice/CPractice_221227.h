#pragma once
#include "CPractice.h"
class CPractice_221227 : 
	public CPractice
{
public: 
	CPractice_221227();
	~CPractice_221227();

private:
	enum class FUNC : int { ONE = 1, TWO, THREE, FOUR, FIVE};
	enum class TEST_FUNC : int { ONE = 1, TWO, THREE, FOUR, FIVE};
	std::unique_ptr<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>> m_uniq_map_func;
	std::unique_ptr<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>> m_uniq_map_testfunc;

private:
	// CPractice을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void render() noexcept override;
	virtual int update() override;
	virtual void release() override;

private:
	void init_func(void);
	void init_testfunc(void);

private:
	template<typename... Args>
	auto build_array(Args&&... _args)
		->std::array<std::common_type_t<Args...>, sizeof ...(_args)>
	{ return { std::forward < std::common_type_t<Args...>>((Args&&)_args)... }; }

};

