#include <iostream>

#include "ProcessTable.hpp"
#include "InputParser.hpp"

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
  else if (args[0] == "wait")
  {
    if (args.size() < 2 || args[1] == "")
    {
      throw "PID required\n";
    }
    table.WaitJob(std::stoi(args[1]));
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