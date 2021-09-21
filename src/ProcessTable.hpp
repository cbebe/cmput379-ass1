#include <string>
#include <map>
#include "Process.hpp"

class ProcessTable
{
public:
  void PrintProcesses() const;
  void NewJob(std::string cmd);
  void NewJob(std::string cmd, bool inBackground);
  void KillJob(int pid);

private:
  void addProcess(Process p);
  int createProcess(std::string cmd, bool inBackground);
  std::map<int, Process> processes;
};