#ifndef PROCESS_H_
#define PROCESS_H_

#include <string>

#include "InputOptions.h"
#include "PsEntry.h"

typedef enum {
  // process is running in background
  RUNNING = 'R',
  // process in background is suspended
  SUSPENDED = 'S',
  // process finished running in background, should wait
  ZOMBIE = 'Z',
  // parent waited and finished running child process
  DONE = 'D'
} Status;

class Process {
public:
  static void Sleep(int seconds);
  static Process from(std::string const &cmd, InputOptions options);
  static void PrintResourceUsage();
  std::string PrintProcess(PsEntry entry) const;
  void Kill();
  void Wait();
  void Resume();
  void Suspend();
  int GetPid() const;
  std::string GetCmd() const;
  Status GetStatus() const;
  void SetStatus(Status s);

private:
  Process(int pid, std::string const &cmd);
  int pid;
  Status status;
  std::string cmd;
};

#endif // PROCESS_H_
