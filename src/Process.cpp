#include "Process.h"

#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iomanip>
#include <iostream>
#include <sstream>

Process Process::from(std::string const &cmd, InputOptions options) {
  pid_t pid = fork();
  if (pid < 0) {
    std::cout << "Error forking child process";
    exit(1);
  } else if (pid == 0) {
    // child process

    /**
     * Tried this first:
     * https://stackoverflow.com/questions/7048888/stdvectorstdstring-to-char-array
     * but that would mean i had to call delete on the array and its c
     * strings after calling execvp which is probably impossible since the
     * program is already replaced
     *
     * Ended up using this:
     * https://stackoverflow.com/questions/52490877/execvp-using-vectorstring
     */
    std::vector<char *> arr;
    arr.reserve(options.cmdArgs.size() + 1);
    // still have to use pointers, so i just ended up using const_cast to
    // remove the const
    for (auto const &sp : options.cmdArgs) {
      arr.push_back(const_cast<char *>(sp.c_str()));
    }

    // null terminator for c-style array
    arr.push_back(nullptr);
    if (execvp(arr[0], arr.data()) < 0) {
      std::cout << "execvp failed\n";
      exit(1);
    }
  }
  // parent process, create Process object

  Process p = Process(pid, cmd);

  if (!options.inBackground) {
    int status;
    waitpid(pid, &status, 0);
    p.SetStatus(DONE);
  }

  return p;
}

void Process::PrintResourceUsage() {
  struct rusage usage;
  getrusage(RUSAGE_CHILDREN, &usage);

  std::cout << "User time = \t" << usage.ru_utime.tv_sec << " seconds\n"
            << "Sys  time = \t" << usage.ru_stime.tv_sec << " seconds\n";
}

Process::Process(int pid, std::string const &cmd) {
  this->cmd = cmd;
  this->pid = pid;
  this->status = RUNNING;
}

std::string Process::PrintProcess(PsEntry entry) const {
  std::stringstream s;
  Status currentStatus = entry.zombie ? ZOMBIE : status;
  s << std::setw(5) << pid << std::setw(2) << (char)currentStatus
    << std::setw(4) << entry.time << " " << cmd;
  return s.str();
};

void Process::Sleep(int seconds) {
  if (seconds < 0) {
    throw "Seconds must be a positive integer";
  }

  sleep(seconds);
}

void Process::Kill() {
  if (kill(pid, SIGKILL) != 0) {
    throw "Kill failed";
  }

  // it's a zombie process by this point, might as well reap
  Wait();
}

void Process::Wait() {
  int status;
  // don't let program hang by waiting for a suspended process
  Resume();
  waitpid(pid, &status, 0);
}

void Process::Resume() {
  if (this->status == RUNNING) {
    throw "Process already running";
  }

  if (kill(pid, SIGCONT) != 0) {
    throw "Resume failed";
  }

  this->status = RUNNING;
}

void Process::Suspend() {
  if (this->status == SUSPENDED) {
    throw "Process already suspended";
  }

  if (kill(pid, SIGSTOP) != 0) {
    throw "Suspend failed";
  }

  this->status = SUSPENDED;
}

int Process::GetPid() const { return pid; };

std::string Process::GetCmd() const { return cmd; }

void Process::SetStatus(Status s) { this->status = s; };

Status Process::GetStatus() const { return status; };
