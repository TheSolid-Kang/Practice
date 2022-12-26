#pragma once
#include "Headers.h"

class CPractice
{
public:
	CPractice();
	virtual ~CPractice();

protected:
	std::list<TString> m_list_title;


public:
	virtual int execute() final;
protected:
	virtual void initialize() = 0;
	virtual void render() noexcept = 0;
	virtual int update() = 0;
	virtual void release() = 0;
};