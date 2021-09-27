#include "InputParser.h"

#include <iostream>
#include <sstream>

#define LINE_LENGTH 100  // Max # of characters in an input line
#define MAX_LENGTH 20    // Max # of characters in an argument

using std::string;
using StrArr = std::vector<string>;

// https://www.quora.com/How-do-I-split-a-string-by-space-into-an-array-in-c++
StrArr InputParser::Tokenize(string const& input) {
  std::istringstream iss(input);
  StrArr tokens;
  for (string s; iss >> s;) {
    tokens.push_back(s);
  }

  return tokens;
}

StrArr InputParser::Split(string const& input, char delim) {
  std::stringstream ss(input);
  StrArr tokens;
  for (string s; std::getline(ss, s, delim);) {
    tokens.push_back(s);
  }

  return tokens;
}

void InputParser::ReadInput() {
  std::getline(std::cin, input);

  if (input == "") {
    return;
  }

  if (!checkLineLength()) {
    throw "Line too long";
  }

  args = Tokenize(input);

  if (!CheckNumberArgs()) {
    throw "Too many arguments";
  }

  if (!checkArgsLength()) {
    throw "Argument too long";
  }
}

InputOptions InputParser::GetCmdOptions() const {
  InputOptions options;

  // i would've used a range-based for loop
  // but i'm not sure how i would check that '&' is the last argument
  for (unsigned int i = 0; i < args.size(); i++) {
    string arg = args[i];
    switch (arg.at(0)) {
      case '&':
        // makes sure that there's a command
        if (arg != "&" || args.size() == 1 || i != args.size() - 1)
          throw "Invalid input of '&'";

        options.inBackground = true;
        break;
      case '>':
        options.outputFiles.push_back(arg.substr(1));
        break;
      case '<':
        options.inputFiles.push_back(arg.substr(1));
        break;
      default:
        options.cmdArgs.push_back(arg);
    }
  }

  // i wanted to implement just piping to files from stdin and from files to
  // stdout but that wasn't part of the assignment specification maybe some
  // other time
  if (options.cmdArgs.size() < 1) {
    throw "No command given";
  }

  return options;
}

int InputParser::RequireInt(const char* message) {
  try {
    if (args.size() > 2) {
      throw "Wrong number of args";
    }

    return std::stoi(args[1]);
  } catch (std::invalid_argument& e) {
    throw message;
  }
}

string InputParser::Input() const { return input; }

StrArr InputParser::Args() const { return args; }

bool InputParser::CheckNumberArgs() const {
  return args.size() <= MAX_ARGS + 1;
}

bool InputParser::checkLineLength() const {
  return input.size() <= LINE_LENGTH;
}

bool InputParser::checkArgsLength() const {
  for (auto const& a : args) {
    if (a.length() > 20) {
      return false;
    }
  }

  return true;
}
