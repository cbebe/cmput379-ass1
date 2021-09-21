#include "ProcessTable.hpp"
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <iostream>

#define MAX_PT_ENTRIES 32 // Max entries in the Process Table

void ProcessTable::PrintProcesses() const
{
  std::cout << "Running processes:\n";
  size_t numProcesses = processes.size();
  if (numProcesses > 0)
  {
    std::cout << " #    PID S SEC COMMAND\n";
    int i = 0;
    for (auto &p : processes)
    {
      std::cout << std::setw(2) << i++ << ": " << p.second.PrintProcess() << std::endl;
    }
  }
  std::cout << "Processes = \t" << numProcesses << " active\n"
            << "Completed processes:\n"
            << "User time = \t" << 0 << " seconds\n"
            << "Sys  time = \t" << 0 << " seconds" << std::endl;
}

void ProcessTable::PrintResourcesUsed() const
{
  std::cout << "Resources used\n"
            << "User time = \t" << 0 << " seconds\n"
            << "Sys  time = \t" << 0 << " seconds" << std::endl;
}

void ProcessTable::NewJob(std::string const &cmd)
{
  NewJob(cmd, false);
}

void ProcessTable::NewJob(std::string const &cmd, bool inBackground)
{
  if (processes.size() > MAX_PT_ENTRIES - 1)
  {
    throw "Max Process table entries exceeded\n";
  }

  int pid = createProcess(cmd, inBackground);
  addProcess(Process(pid, cmd));
}

void ProcessTable::KillJob(int pid)
{
  std::cout << "Kill " << pid << std::endl;
}

// creates the process and returns its pid
// call fork here
int ProcessTable::createProcess(std::string cmd, bool inBackground)
{
  std::cout << cmd << inBackground << std::endl;
  return rand() % 10000;
}

void ProcessTable::addProcess(Process p)
{
  processes.emplace(p.getPid(), p);
}