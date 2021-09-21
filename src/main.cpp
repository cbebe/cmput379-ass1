#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ProcessTable.hpp"

#define MAX_PT_ENTRIES 32 // Max entries in the Process Table
#define LINE_LENGTH 100   // Max # of characters in an input line
#define MAX_ARGS 7        // Max number of arguments to a command
#define MAX_LENGTH 20     // Max # of characters in an argument

std::string getInput()
{
  std::cout << "shell379> " << std::flush;
  std::string input;
  std::getline(std::cin, input);
  return input;
}

// https://java2blog.com/split-string-space-cpp/
std::vector<std::string> tokenize(std::string const &str)
{
  std::vector<std::string> out;
  // construct a stream from the string
  std::stringstream ss(str);

  std::string s;
  while (std::getline(ss, s, ' '))
  {
    out.push_back(s);
  }
  return out;
}

void endShell()
{
  // end the execution of shell379

  // wait until all processes are initiated by the shell are complete

  // print out the total user and system time for all processes run by the shell
  std::cout << "Resources used\n"
            << "User time = \t" << 0 << " seconds\n"
            << "Sys  time = \t" << 0 << " seconds" << std::endl;
  exit(0);
}

std::string printRunningProcesses()
{
  return "";
}

void kill(int pid)
{
  // kill process pid
}

void resume(int pid)
{
  // resume process pid. this undoes a suspend
}

void suspend(int pid)
{
  // suspend execution of process pid. a resume will awaken it
}

void sleep(int seconds)
{
  // sleep for given seconds
}

void execute(char *cmd, char **arg)
{
  // spawn process to execute command with 0 or more arguments
}

// special arguments
// & - last argument - must run in background
// <fname - take input from a file named fname
// >fname - print output to a file named fname

bool checkLineLength(std::string const &input)
{
  return input.size() <= LINE_LENGTH;
}

bool checkNumberArgs(std::vector<std::string> const &args)
{
  return args.size() <= MAX_ARGS + 1;
}

bool checkArgsLength(std::vector<std::string> const &args)
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

void run(ProcessTable &table)
{
  std::string input = getInput();
  if (input == "")
  {
    return;
  }
  if (!checkLineLength(input))
  {
    std::cout << "Line too long" << std::endl;
    return;
  }

  std::vector<std::string> args = tokenize(input);

  if (!checkNumberArgs(args))
  {
    std::cout << "Too many arguments" << std::endl;
    return;
  }
  if (!checkArgsLength(args))
  {
    std::cout << "Argument too long" << std::endl;
    return;
  }

  if (args[0] == "exit")
  {
    endShell();
  }
  else if (args[0] == "jobs")
  {
    table.PrintProcesses();
  }

  table.NewJob(input);
}

int main(int argc, char *argv[])
{
  ProcessTable table = ProcessTable();
  while (true)
  {
    run(table);
  }
}