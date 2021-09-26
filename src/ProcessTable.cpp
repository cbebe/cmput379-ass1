#include "ProcessTable.hpp"
#include <iomanip>
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
      std::cout << std::setw(2) << i++ << ": " << p.second.PrintProcess() << "\n";
    }
  }
  std::cout << "Processes = \t" << numProcesses << " active\n"
            << "Completed processes:\n";
  Process::PrintResourceUsage();
}

void ProcessTable::PrintResourcesUsed() const
{
  std::cout << "Resources used\n";
  Process::PrintResourceUsage();
}

void ProcessTable::NewJob(const std::string &cmd, InputOptions const &options)
{
  // spawn process to execute command with 0 or more arguments
  if (processes.size() > MAX_PT_ENTRIES - 1)
    throw "Max Process table entries exceeded";

  Process process = Process::from(cmd, options);
  if (process.GetStatus() != DONE)
    addProcess(process);
}

// special arguments
// & - last argument - must run in background
// <fname - take input from a file named fname
// >fname - print output to a file named fname

void ProcessTable::KillJob(int pid)
{
  // kill process pid
  getProcess(pid).Kill();
  removeProcess(pid);
}

void ProcessTable::SuspendJob(int pid)
{
  // suspend execution of process pid. a resume will awaken it
  getProcess(pid).Suspend();
}

void ProcessTable::WaitJob(int pid)
{
  getProcess(pid).Wait();
  removeProcess(pid);
}

void ProcessTable::Sleep(int seconds)
{
  // sleep for given seconds
  Process::Sleep(seconds);
}

void ProcessTable::ResumeJob(int pid)
{
  // resume process pid. this undoes a suspend
  getProcess(pid).Resume();
}

void ProcessTable::addProcess(Process p)
{
  processes.emplace(p.GetPid(), p);
}

void ProcessTable::removeProcess(int pid)
{
  processes.erase(pid);
}

Process &ProcessTable::getProcess(int pid)
{
  try
  {
    return processes.at(pid);
  }
  catch (std::out_of_range &e)
  {
    throw "Process not found";
  }
}