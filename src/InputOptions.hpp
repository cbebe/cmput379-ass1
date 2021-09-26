#pragma once
#include <vector>
#include <string>

#define MAX_ARGS 7 // Max number of arguments to a command

class InputOptions
{
public:
  InputOptions() : inBackground(false) {}
  bool inBackground;
  std::vector<std::string> cmdArgs;
  std::vector<std::string> inputFiles;
  std::vector<std::string> outputFiles;
};
