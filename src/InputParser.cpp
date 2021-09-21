#include "InputParser.hpp"
#include <iostream>
#include <sstream>

#define LINE_LENGTH 100 // Max # of characters in an input line
#define MAX_ARGS 7      // Max number of arguments to a command
#define MAX_LENGTH 20   // Max # of characters in an argument

void InputParser::ReadInput()
{
  std::cout << "shell379> " << std::flush;
  std::getline(std::cin, input);

  if (input == "")
  {
    throw "";
  }
  if (!checkLineLength())
  {
    throw "Line too long\n";
  }
  tokenize();
  if (!checkNumberArgs())
  {
    throw "Too many arguments\n";
  }
  if (!checkArgsLength())
  {
    throw "Argument too long\n";
  }
}

std::string InputParser::GetInput() const
{
  return input;
}

std::vector<std::string> InputParser::GetArgs() const
{
  return args;
}

// https://java2blog.com/split-string-space-cpp/
void InputParser::tokenize()
{
  // construct a stream from the string
  std::stringstream ss(input);
  args.clear();
  std::string s;
  while (std::getline(ss, s, ' '))
  {
    args.push_back(s);
  }
}

bool InputParser::checkNumberArgs() const
{
  return args.size() <= MAX_ARGS + 1;
}

bool InputParser::checkLineLength() const
{
  return input.size() <= LINE_LENGTH;
}
bool InputParser::checkArgsLength() const
{
  for (auto const &a : args)
  {
    if (a.length() > 20)
    {
      return false;
    }
  }

  return true;
}