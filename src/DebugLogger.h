#pragma once
#include <string>

class DebugLogger
{
public:
  static void Log(const std::string &message);
  static void LogWarning(const std::string &message);
  static void LogError(const std::string &message);
};
