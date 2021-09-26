#ifndef PROCESS_TABLE_H_
#define PROCESS_TABLE_H_

#include <string>
#include <unordered_map>

#include "InputOptions.h"
#include "Process.h"

class ProcessTable
{
public:
  void PrintProcesses () const;
  void PrintResourcesUsed () const;
  void NewJob (const std::string &cmd, InputOptions const &options);
  void KillJob (int pid);
  void SuspendJob (int pid);
  void ResumeJob (int pid);
  void WaitJob (int pid);
  void Sleep (int seconds);

private:
  void addProcess (Process p);
  void removeProcess (int pid);
  Process &getProcess (int pid);
  std::unordered_map<int, Process> processes;
};

#endif // PROCESS_TABLE_H_
