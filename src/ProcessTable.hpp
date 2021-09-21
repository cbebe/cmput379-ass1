#include <string>
#include <map>
#include "Process.hpp"

class ProcessTable
{
public:
  void PrintProcesses() const;
  void PrintResourcesUsed() const;
  void NewJob(std::string const &cmd);
  void NewJob(std::string const &cmd, bool inBackground);
  void KillJob(int pid);
  void SuspendJob(int pid);
  void ResumeJob(int pid);
  void WaitJob(int pid);
  void Sleep(int seconds);

private:
  void addProcess(Process p);
  int createProcess(std::string cmd, bool inBackground);
  std::map<int, Process> processes;
};