#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Process.hpp"

Process::Process(int pid, std::string cmd)
{
  this->cmd = cmd;
  this->pid = pid;
}

std::string Process::PrintProcess() const
{
  std::stringstream s;
  s << std::setw(5) << pid << std::setw(2) << "R" << std::setw(4) << 0 << " " << cmd;
  return s.str();
};

void KillProcess() {}

int Process::getPid() const
{
  return pid;
};