#ifndef INPUT_PARSER_H_
#define INPUT_PARSER_H_

#include <string>
#include <vector>

#include "InputOptions.h"

class InputParser {
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

#endif  // INPUT_PARSER_H_
