#ifndef INPUT_OPTIONS_H_
#define INPUT_OPTIONS_H_

#include <string>
#include <vector>

#define MAX_ARGS 7 // Max number of arguments to a command

class InputOptions {
public:
  InputOptions() : inBackground(false) {}
  bool inBackground;
  std::vector<std::string> cmdArgs;
  std::vector<std::string> inputFiles;
  std::vector<std::string> outputFiles;
};

#endif // INPUT_OPTIONS_H_
