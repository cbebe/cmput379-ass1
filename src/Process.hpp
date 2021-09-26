#pragma once
#include <string>
#include "InputOptions.hpp"

typedef enum
{
  RUNNING = 'R',
  SUSPENDED = 'S'
} Status;

class Process
{
public:
  static void Sleep(int seconds);
  static Process from(std::string const &cmd, InputOptions options);
  std::string PrintProcess() const;
  void Kill();
  void Wait();
  void Resume();
  void Suspend();
  int GetPid() const;

private:
  Process(int pid, std::string const &cmd);
  int pid;
  Status status;
  std::string cmd;
};