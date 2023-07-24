#pragma once
#include <Windows.h>

#include <iostream>

#include <string>
#include <tchar.h>

#include <array>
#include <vector>

#include <list>

#include <set>
#include <map>

#include <functional>

#include <algorithm>

#include <type_traits>

#include <tuple>

#include <sstream>


#if UNICODE 
using TString = std::wstring;
using tifstream = std::wifstream;
using tofstream = std::wofstream;
using tistringstream = std::wistringstream;
using tstring_view = std::wstring_view;
using tstringstream = std::wstringstream;
#define tcout  wcout
#define tcin  wcin
#else
using TString = std::string;
using tifstream = std::ifstream;
using tofstream = std::ofstream;
using tistringstream = std::istringstream;
using tstring_view = std::string_view;
using tstringstream = std::stringstream; 
#define tcout  cout
#define tcin  cin
#endif;

#include "CIO.h"
