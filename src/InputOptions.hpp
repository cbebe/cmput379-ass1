#pragma once
#include <vector>
#include <string>

typedef struct
{
  bool inBackground;
  std::vector<std::string> cmdArgs;
  std::vector<std::string> inputFiles;
  std::vector<std::string> outputFiles;
} InputOptions;
