#pragma once
#include <string>
#include <unordered_map>

#include "Process.hpp"
#include "InputOptions.hpp"

class ProcessTable
{
public:
  void PrintProcesses() const;
  void PrintResourcesUsed() const;
  void NewJob(const std::string &cmd, InputOptions const &options);
  void KillJob(int pid);
  void SuspendJob(int pid);
  void ResumeJob(int pid);
  void WaitJob(int pid);
  void Sleep(int seconds);

private:
  void addProcess(Process p);
  void removeProcess(int pid);
  Process &getProcess(int pid);
  std::unordered_map<int, Process> processes;
};