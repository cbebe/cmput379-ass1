#include "ProcessTable.h"
#include "InputParser.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

#define MAX_PT_ENTRIES 32 // Max entries in the Process Table

using PsEntry = struct {
  int time;
  bool zombie;
};

using PsEntryTable = std::unordered_map<int, PsEntry>;

std::vector<std::string> getPsOutput() {
  // https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("ps", "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  std::vector<std::string> psLines = InputParser::Split(result, '\n');
  // remove first line which is just a table heading
  psLines.erase(psLines.begin());
  return psLines;
}

PsEntryTable getPsEntries(std::vector<std::string> const &psLines) {
  PsEntryTable psEntries;
  for (auto const &s : psLines) {
    // ps line is this format:
    // PID TTY HH:MM:SS: CMD
    std::vector<std::string> psLine = InputParser::Tokenize(s);
    int pid = std::stoi(psLine[0]);
    // time in seconds
    int time = std::stoi(InputParser::Split(psLine[2], ':')[2]);
    // this is assuming that the file has no "<defunct>" in its name
    bool zombie = psLine[psLine.size() - 1] == "<defunct>";
    PsEntry entry = {time, zombie};
    psEntries.emplace(pid, entry);
  }

  return psEntries;
}

void ProcessTable::PrintProcesses() const {
  PsEntryTable psEntries = getPsEntries(getPsOutput());
  std::cout << "Running processes:\n";
  size_t numProcesses = processes.size();
  if (numProcesses > 0) {
    std::cout << " #    PID S SEC COMMAND\n";
    int i = 0;
    for (auto const &p : processes) {
      PsEntry entry = psEntries.at(p.second.GetPid());
      Status s = entry.zombie ? ZOMBIE : p.second.GetStatus();
      std::cout << std::setw(2) << i++ << ": " << std::setw(5)
                << p.second.GetPid() << std::setw(2) << (char)s << std::setw(4)
                << entry.time << " " << p.second.GetCmd() << "\n";
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
  if (processes.size() > MAX_PT_ENTRIES - 1) {
    throw "Max Process table entries exceeded";
  }

  Process process = Process::from(cmd, options);
  if (process.GetStatus() != DONE) {
    addProcess(process);
  }
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
