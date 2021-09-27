#include "ProcessTable.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

#include "InputParser.h"

#define MAX_PT_ENTRIES 32  // Max entries in the Process Table

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

std::unordered_map<int, int> getPsEntries(
    std::vector<std::string> const& psLines) {
  std::unordered_map<int, int> psEntries;
  for (auto const& s : psLines) {
    // ps line is this format:
    // PID TTY HH:MM:SS: CMD
    std::vector<std::string> psLine = InputParser::Tokenize(s);
    int pid = std::stoi(psLine[0]);
    // time in seconds
    int time = std::stoi(InputParser::Split(psLine[2], ':')[2]);
    psEntries.emplace(pid, time);
  }

  return psEntries;
}

void ProcessTable::PrintProcesses() const {
  std::unordered_map<int, int> psEntries = getPsEntries(getPsOutput());
  std::cout << "Running processes:\n";
  size_t numProcesses = processes.size();
  if (numProcesses > 0) {
    std::cout << " #    PID S SEC COMMAND\n";
    int i = 0;
    for (auto const& p : processes) {
      std::cout << std::setw(2) << i++ << ": "
                << p.second.PrintProcess(psEntries.at(p.first)) << "\n";
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

void ProcessTable::NewJob(const std::string& cmd, InputOptions const& options) {
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

Process& ProcessTable::getProcess(int pid) {
  try {
    return processes.at(pid);
  } catch (std::out_of_range& e) {
    throw "Process not found";
  }
}
