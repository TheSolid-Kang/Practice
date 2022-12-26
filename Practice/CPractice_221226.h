#pragma once
#include "CPractice.h"
class CPractice_221226 :public CPractice
{
public:
	CPractice_221226();
	~CPractice_221226();



private:
	// CPractice을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void render() noexcept override;
	virtual int update() override;
	virtual void release() override;
};

