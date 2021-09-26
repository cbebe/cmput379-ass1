#include <iostream>

#include "ProcessTable.hpp"
#include "InputParser.hpp"

void run(InputParser &parser, ProcessTable &table)
{
  std::cout << "shell379> " << std::flush;
  parser.ReadInput();
  std::string input = parser.GetInput();
  if (input == "")
    return;
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
  else if (args[0] == "kill")
  {
    table.KillJob(parser.RequireInt("PID required"));
  }
  else if (args[0] == "resume")
  {
    table.ResumeJob(parser.RequireInt("PID required"));
  }
  else if (args[0] == "sleep")
  {
    table.Sleep(parser.RequireInt("seconds required"));
  }
  else if (args[0] == "suspend")
  {
    table.SuspendJob(parser.RequireInt("PID required"));
  }
  else if (args[0] == "wait")
  {
    table.WaitJob(parser.RequireInt("PID required"));
  }
  else
  {
    table.NewJob(input, parser.GetCmdOptions());
  }
}

int main()
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
      std::cout << msg << "\n";
    }
  }
}