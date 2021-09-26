#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

#include <csignal>
#include <cstring>

#include "Process.hpp"

Process Process::from(std::string const &cmd, InputOptions options)
{
  // creates the process and returns its pid
  // call fork here
  bool fromStdIn = options.inputFiles.size() == 0;
  bool toStdOut = options.outputFiles.size() == 0;

  int pid = fork();
  if (pid < 0)
  {
    std::cout << "Error forking child process";
    exit(1);
  }
  else if (pid == 0)
  {
    // tried this first, but that would mean i had to delete after calling execvp, which is impossible
    // https://stackoverflow.com/questions/7048888/stdvectorstdstring-to-char-array
    // ended up using this
    // https://stackoverflow.com/questions/52490877/execvp-using-vectorstring
    std::vector<char *> arr;
    arr.reserve(options.cmdArgs.size() + 1);
    // still have to use pointers, so i just ended up using const_cast to remove the const
    for (std::string &sp : options.cmdArgs)
      arr.push_back(const_cast<char *>(sp.c_str()));

    // null terminator for c-style array
    arr.push_back(nullptr);
    if (execvp(arr[0], arr.data()) < 0)
    {
      std::cout << "execvp failed\n";
      exit(1);
    }
  }

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
    throw "Seconds must be a positive integer";

  sleep(seconds);
}

void Process::Kill()
{
  // kill process here
  if (!kill(pid, SIGKILL))
    throw "Kill failed";
}

void Process::Wait()
{
  int status;
  // wait for process to finish here
  waitpid(pid, &status, 0);
}

void Process::Resume()
{
  if (this->status == RUNNING)
    throw "Process already running";

  // resume here
  if (!kill(pid, SIGCONT))
    throw "Resume failed";

  this->status = RUNNING;
}

void Process::Suspend()
{
  if (this->status == SUSPENDED)
    throw "Process already suspended";

  // suspend here
  if (!kill(pid, SIGSTOP))
    throw "Suspend failed";

  this->status = SUSPENDED;
}

int Process::GetPid() const
{
  return pid;
};