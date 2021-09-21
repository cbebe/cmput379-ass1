#pragma once
#include <string>
#include <vector>

#include "InputOptions.hpp"

class InputParser
{
public:
  void ReadInput();
  std::string GetInput() const;
  std::vector<std::string> GetArgs() const;
  InputOptions GetOptions() const;
  void RequireArgs(size_t argc, const char *message);

private:
  void tokenize();
  bool checkNumberArgs() const;
  bool checkLineLength() const;
  bool checkArgsLength() const;
  std::vector<std::string> args;
  std::string input;
  InputOptions options;
};