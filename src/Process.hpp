#pragma once
#include <string>

class Process
{
public:
  Process(int pid, std::string cmd);
  std::string PrintProcess() const;
  void KillProcess();

  int getPid() const;

private:
  int pid;
  std::string cmd;
};