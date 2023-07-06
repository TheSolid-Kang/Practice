#pragma once
#include "CPractice.h"
class CPractice_2 :
	public CPractice
{
public:
	CPractice_2();
	~CPractice_2();

private:
	enum class FUNC : int { ONE = 1, TWO, THREE, FOUR, FIVE };
	enum class TEST_FUNC : int { ONE = 1, TWO, THREE, FOUR, FIVE };
	std::unique_ptr<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>> m_uniq_map_func;
	std::unique_ptr<std::map<size_t, std::function<std::shared_ptr<void>(const void*)>>> m_uniq_map_testfunc;

private:
	// CPractice을(를) 통해 상속됨
	virtual void _Initialize(void) override;
	virtual void _InitFunc(void) override;
	virtual void _InitSelectedFunc(void) override;
	virtual void _Render(void) override;
	virtual void _Render(const void* _p_void) override;
	virtual int _Update(int _event = 0) override;
	virtual void _Release(void) override;

private:
	template<typename... Args>//분석 필요: 이해 없이 컴파일되기에 사용하는 코드.
	auto _BuildArray(Args&&... _args)
		->std::array<std::common_type_t<Args...>, sizeof ...(_args)>
	{ return { std::forward < std::common_type_t<Args...>>((Args&&)_args)... }; }
};