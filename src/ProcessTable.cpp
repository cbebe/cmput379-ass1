#include "ProcessTable.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>

#define MAX_PT_ENTRIES 32  // Max entries in the Process Table

void ProcessTable::PrintProcesses() const {
  std::cout << "Running processes:\n";
  size_t numProcesses = processes.size();
  if (numProcesses > 0) {
    std::cout << " #    PID S SEC COMMAND\n";
    int i = 0;
    for (auto const &p : processes) {
      std::cout << std::setw(2) << i++ << ": " << p.second.PrintProcess()
                << "\n";
    }
  }
  std::cout << "Processes = \t" << numProcesses << " active\n"
            << "Completed processes:\n";
  Process::PrintResourceUsage();
}

void ProcessTable::PrintResourcesUsed() const {
  std::cout << "Resources used\n";
  Process::PrintResourceUsage();
}

void ProcessTable::NewJob(const std::string &cmd, InputOptions const &options) {
  if (processes.size() > MAX_PT_ENTRIES - 1)
    throw "Max Process table entries exceeded";

  Process process = Process::from(cmd, options);
  if (process.GetStatus() != DONE) addProcess(process);
}

void ProcessTable::KillJob(int pid) {
  getProcess(pid).Kill();
  removeProcess(pid);
}

void ProcessTable::SuspendJob(int pid) { getProcess(pid).Suspend(); }

void ProcessTable::WaitJob(int pid) {
  getProcess(pid).Wait();
  removeProcess(pid);
}

void ProcessTable::Sleep(int seconds) { Process::Sleep(seconds); }

void ProcessTable::ResumeJob(int pid) { getProcess(pid).Resume(); }

void ProcessTable::addProcess(Process p) { processes.emplace(p.GetPid(), p); }

void ProcessTable::removeProcess(int pid) { processes.erase(pid); }

Process &ProcessTable::getProcess(int pid) {
  try {
    return processes.at(pid);
  } catch (std::out_of_range &e) {
    throw "Process not found";
  }
}
