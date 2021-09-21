#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ProcessTable.hpp"
#include "InputParser.hpp"

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

void run(InputParser &parser, ProcessTable &table)
{
  parser.ReadInput();
  std::string input = parser.GetInput();
  std::vector<std::string> args = parser.GetArgs();

  if (args[0] == "exit")
  {
    table.PrintResourcesUsed();
    exit(0);
  }
  else if (args[0] == "jobs")
  {
    table.PrintProcesses();
  }
  else
  {
    table.NewJob(input);
  }
}

int main(int argc, char *argv[])
{
  InputParser parser = InputParser();
  ProcessTable table = ProcessTable();
  while (true)
  {
    try
    {
      run(parser, table);
    }
    catch (const char *msg)
    {
      std::cout << msg;
    }
  }
}