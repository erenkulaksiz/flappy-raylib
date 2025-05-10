#include "DebugLogger.h"
#include <stdio.h>

void DebugLogger::Log(const std::string &message)
{
  printf("[INFO] %s\n", message.c_str());
}

void DebugLogger::LogWarning(const std::string &message)
{
  printf("[WARNING] %s\n", message.c_str());
}

void DebugLogger::LogError(const std::string &message)
{
  printf("[ERROR] %s\n", message.c_str());
}