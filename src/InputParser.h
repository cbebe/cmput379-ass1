#ifndef INPUT_PARSER_H_
#define INPUT_PARSER_H_

#include <string>
#include <vector>

#include "InputOptions.h"

class InputParser {
 public:
  static std::vector<std::string> Tokenize(std::string const& input);
  static std::vector<std::string> Split(std::string const& input, char delim);
  void ReadInput();
  std::string Input() const;
  std::vector<std::string> Args() const;
  InputOptions GetCmdOptions() const;
  int RequireInt(const char* message);

 private:
  bool CheckNumberArgs() const;
  bool checkLineLength() const;
  bool checkArgsLength() const;
  std::vector<std::string> args;
  std::string input;
};

#endif  // INPUT_PARSER_H_
