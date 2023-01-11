#pragma once
#include "Headers.h"
#include "Enum.h"
#include <boost/noncopyable.hpp>

class IPractice
{
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

class CPractice : public IPractice, public boost::noncopyable
{
public:
	CPractice();
	virtual ~CPractice();

protected:
	std::list<TString> m_list_title;


public:
	virtual int Execute() final;

protected:
	// IPractice을(를) 통해 상속됨
	virtual void initialize(void) override;
	virtual void init_func(void) override;
	virtual void init_selected_func(void) override;
	virtual void render(void) override;
	virtual void render(const void* _p_void) override;
	void render(TString& _str) override;
	void render(TString&& _str) { render(_str); };
	virtual int update(int _event = 0) override;
	virtual void release(void) override;
};