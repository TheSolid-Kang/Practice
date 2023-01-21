#pragma once
#include "Headers.h"
#include "Enum.h"

class IPractice
{
protected:
	virtual void _Initialize(void) = 0;
	virtual void _InitFunc(void) = 0;
	virtual void _InitSelectedFunc(void) = 0;
	virtual void _Render(void) = 0;
	virtual void _Render(const void* _p_void) = 0;
	virtual void _Render(TString& _str) = 0;
	virtual int _Update(int _event = 0) = 0;
	virtual void _Release(void) = 0;
};

class CPractice : public IPractice
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
	virtual void _Initialize(void) override;
	virtual void _InitFunc(void) override;
	virtual void _InitSelectedFunc(void) override;
	virtual void _Render(void) override;
	virtual void _Render(const void* _p_void) override;
	void _Render(TCHAR* _str) { _Render(TString(_str)); }
	void _Render(TString& _str) override;
	void _Render(TString&& _str) { _Render(_str); };
	virtual int _Update(int _event = 0) override;
	virtual void _Release(void) override;
};