#pragma once
#include <iostream>
#include <string>
#include <tchar.h>

#include <vector>
#include <sstream>
#if UNICODE 
using TString = std::wstring;
using tistringstream = std::wistringstream;
#else
using TString = std::string;
using tistringstream = std::istringstream;
#endif;
class CMyEtc
{
public:
	static std::vector<TString> Split(TString& _str, TCHAR _delimiter)
	{
		std::vector<TString> vecResult;
		vecResult.reserve(1024);
		tistringstream iss(_str);
		TString buffer;

		while (std::getline(iss, buffer, _delimiter))
		{
			vecResult.push_back(buffer);
		}
		return vecResult;
	}

};