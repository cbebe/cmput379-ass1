#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

#include "Process.hpp"

Process Process::from(std::string const &cmd, InputOptions options)
{
  // creates the process and returns its pid
  // call fork here
  int pid = rand();
  return Process(pid, cmd);
}

Process::Process(int pid, std::string const &cmd)
{
  this->cmd = cmd;
  this->pid = pid;
  this->status = RUNNING;
}

std::string Process::PrintProcess() const
{
  std::stringstream s;
  s << std::setw(5) << pid << std::setw(2) << (char)status << std::setw(4) << 0 << " " << cmd;
  return s.str();
};

void Process::Sleep(int seconds)
{
  if (seconds < 0)
    throw "Seconds must be a positive integer\n";

  sleep(seconds);
}

void Process::Kill()
{
  // kill process here
}

void Process::Wait()
{
  // wait for process to finish here
}

void Process::Resume()
{
  if (this->status == RUNNING)
    throw "Process already running";

  // resume here

  this->status = RUNNING;
}

void Process::Suspend()
{
  if (this->status == SUSPENDED)
    throw "Process already suspended";

  // suspend here

  this->status = SUSPENDED;
}

int Process::GetPid() const
{
  return pid;
};