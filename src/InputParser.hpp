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
  InputOptions GetCmdOptions() const;
  int RequireInt(const char *message);

private:
  void tokenize();
  bool checkNumberArgs() const;
  bool checkLineLength() const;
  bool checkArgsLength() const;
  std::vector<std::string> args;
  std::string input;
};