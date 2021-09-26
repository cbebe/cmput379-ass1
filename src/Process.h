#ifndef PROCESS_H_
#define PROCESS_H_

#include <string>
#include "InputOptions.h"

typedef enum
{
  RUNNING = 'R',
  SUSPENDED = 'S',
  ZOMBIE = 'Z',
  DONE = 'D'
} Status;

class Process
{
public:
  static void Sleep(int seconds);
  static Process from(std::string const &cmd, InputOptions options);
  static void PrintResourceUsage();
  std::string PrintProcess() const;
  void Kill();
  void Wait();
  void Resume();
  void Suspend();
  int GetPid() const;
  Status GetStatus() const;
  void SetStatus(Status s);

private:
  Process(int pid, std::string const &cmd);
  int pid;
  Status status;
  std::string cmd;
};

#endif // PROCESS_H_
