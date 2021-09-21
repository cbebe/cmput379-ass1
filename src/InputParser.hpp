#include <string>
#include <vector>

class InputParser
{
public:
  void ReadInput();
  std::string GetInput() const;
  std::vector<std::string> GetArgs() const;

private:
  void tokenize();
  bool checkNumberArgs() const;
  bool checkLineLength() const;
  bool checkArgsLength() const;
  std::vector<std::string> args;
  std::string input;
};