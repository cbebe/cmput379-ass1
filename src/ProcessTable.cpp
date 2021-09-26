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

void ProcessTable::NewJob(const std::string &cmd, InputOptions const &options)
{
  // spawn process to execute command with 0 or more arguments
  if (processes.size() > MAX_PT_ENTRIES - 1)
  {
    throw "Max Process table entries exceeded\n";
  }

  int pid = createProcess(options);
  addProcess(Process(pid, cmd));
}

// special arguments
// & - last argument - must run in background
// <fname - take input from a file named fname
// >fname - print output to a file named fname

void ProcessTable::KillJob(int pid)
{
  // kill process pid
  std::cout << "Kill " << pid << std::endl;
}

void ProcessTable::SuspendJob(int pid)
{
  // suspend execution of process pid. a resume will awaken it
  std::cout << "Suspend " << pid << std::endl;
}

void ProcessTable::WaitJob(int pid)
{
  std::cout << "Wait " << pid << std::endl;
}

void ProcessTable::Sleep(int seconds)
{
  // sleep for given seconds
  std::cout << "Sleep " << seconds << std::endl;
}

void ProcessTable::ResumeJob(int pid)
{
  // resume process pid. this undoes a suspend
  std::cout << "Resume " << pid << std::endl;
}

// creates the process and returns its pid
// call fork here
int ProcessTable::createProcess(InputOptions const &options)
{
  for (const std::string &i : options.inputFiles)
  {
    std::cout << i << std::endl;
  }
  return rand() % 10000;
}

void ProcessTable::addProcess(Process p)
{
  processes.emplace(p.getPid(), p);
}

void ProcessTable::removeProcess(int pid)
{
  processes.erase(pid);
}