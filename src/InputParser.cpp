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
    throw "";

  if (!checkLineLength())
    throw "Line too long\n";

  tokenize();

  if (!checkNumberArgs())
    throw "Too many arguments\n";

  if (!checkArgsLength())
    throw "Argument too long\n";
}

InputOptions InputParser::GetCmdOptions() const
{
  // reset options
  InputOptions options;

  // i would've used a range-based for loop
  // but i'm not sure how i would check that & is the last argument
  for (unsigned int i = 0; i < args.size(); i++)
  {
    switch (args[i].at(0))
    {
    case '&':
      // makes sure that there's a command
      if (args[i] != "&" || args.size() == 1 || i != args.size() - 1)
      {
        throw "Invalid input of '&'\n";
      }
      options.inBackground = true;
      break;
    case '>':
      options.outputFiles.push_back(args[i].substr(1));
      break;
    case '<':
      options.inputFiles.push_back(args[i].substr(1));
      break;
    default:
      options.cmdArgs.push_back(args[i]);
    }
  }

  // i wanted to implement just piping to files from stdin and from files to stdout
  // but that wasn't part of the assignment specification
  // maybe some other time
  if (options.cmdArgs.size() < 1)
  {
    throw "No command given";
  }

  return options;
}

int InputParser::RequireInt(const char *message)
{
  try
  {
    if (args.size() > 2)
    {
      throw std::invalid_argument("wrong number of args");
    }

    return std::stoi(args[1]);
  }
  catch (std::invalid_argument &e)
  {
    throw message;
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