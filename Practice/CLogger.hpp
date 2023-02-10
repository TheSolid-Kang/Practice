#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <tchar.h>
#include <Windows.h>
enum LogLevel {
  Error = 1,
  Warn = 2,
  Info = 3,
  Debug = 4
};
class Logger {
private:
#if UNICODE 
  using TString = std::wstring;
  using tifstream = std::wifstream;
  using tofstream = std::wofstream;
#define tcout  wcout
#define tcin  wcin
#else
  using TString = std::string;
  using tifstream = std::ifstream;
  using tofstream = std::ofstream;
#define tcout  tcout
#define tcin  wcin
#endif;
public:

  Logger() : m_logLevel(LogLevel::Info), m_fileStream(GetEXEFilePath() + _T("Log.txt"), std::ios::out) {}
private:
  LogLevel m_logLevel;
  tofstream m_fileStream;

public:
  void Log(LogLevel& level, TString& message) {
    SetLogLevel(level);
    switch (level)
    {
    Error:
      Error(message);
      break;
    Warn:
      Warn(message);
      break;
    Info:
      Info(message);
      break;
    Debug:
      Debug(message);
      break;
    }
  }
private:
  //0. 실행파일 경로 구하기
  TString GetEXEFilePath() {
    TCHAR path[MAX_PATH] = { 0, };
    GetModuleFileName(NULL, path, MAX_PATH);
    TString exe_path = path;
    exe_path = exe_path.substr(0, exe_path.find_last_of(_T("\\/")));
    return exe_path;
  }

  void SetLogLevel(LogLevel level) {
    m_logLevel = level;
  }
  void Error(const TString& message) {
    if (m_logLevel >= LogLevel::Error) {
      std::tcout << "[ERROR]: " << message << std::endl;
      m_fileStream << "[ERROR]: " << message << std::endl;
    }
  }
  void Warn(const TString& message) {
    if (m_logLevel >= LogLevel::Warn) {
      std::tcout << "[WARNING]: " << message << std::endl;
      m_fileStream << "[WARNING]: " << message << std::endl;
    }
  }
  void Info(const TString& message) {
    if (m_logLevel >= LogLevel::Info) {
      std::tcout << "[INFO]: " << message << std::endl;
      m_fileStream << "[INFO]: " << message << std::endl;
    }
  }
  void Debug(const TString& message) {
    if (m_logLevel >= LogLevel::Debug) {
      std::tcout << "[DEBUG]: " << message << std::endl;
      m_fileStream << "[DEBUG]: " << message << std::endl;
    }
  }


};