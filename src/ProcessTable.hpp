#pragma once
#include <string>
#include <map>

#include "Process.hpp"
#include "InputOptions.hpp"

class ProcessTable
{
public:
  void PrintProcesses() const;
  void PrintResourcesUsed() const;
  void NewJob(std::string const &cmd, InputOptions const &options);
  void KillJob(int pid);
  void SuspendJob(int pid);
  void ResumeJob(int pid);
  void WaitJob(int pid);
  void Sleep(int seconds);

private:
  void addProcess(Process p);
  void removeProcess(int pid);
  int createProcess(std::string const &cmd, InputOptions const &options);
  std::map<int, Process> processes;
};