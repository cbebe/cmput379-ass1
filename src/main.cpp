#include <iostream>
#include <string>

std::string getInput()
{
  std::cout << "shell379> " << std::flush;
  std::string input;
  std::cin >> input;
  return input;
}

void endShell()
{
  // end the execution of shell379

  // wait until all processes are initiated by the shell are complete

  // print out the total user and system time for all processes run by the shell
  std::cout << "Resources used\n"
            << "User time = \t" << 0 << " seconds\n"
            << "Sys  time = \t" << 0 << " seconds" << std::endl;
  exit(0);
}

std::string printRunningProcesses()
{
  return "";
}

void jobs()
{
  // display the status of all running processes spawned by shell379
  std::cout << "Running processes:\n"
            << printRunningProcesses()
            << "Processes = \t" << 0 << " active\n"
            << "Completed processes:\n"
            << "User time = \t" << 0 << " seconds\n"
            << "Sys  time = \t" << 0 << " seconds" << std::endl;
}

void kill(int pid)
{
  // kill process pid
}

void resume(int pid)
{
  // resume process pid. this undoes a suspend
}

void suspend(int pid)
{
  // suspend execution of process pid. a resume will awaken it
}

void sleep(int seconds)
{
  // sleep for given seconds
}

void execute(char *cmd, char **arg)
{
  // spawn process to execute command with 0 or more arguments
}

// special arguments
// & - last argument - must run in background
// <fname - take input from a file named fname
// >fname - print output to a file named fname

int main(int argc, char *argv[])
{
  while (true)
  {
    std::string input = getInput();
    if (input == "exit")
    {
      endShell();
    }
    else if (input == "jobs")
    {
      jobs();
    }
    else
    {
      std::cout << input << std::endl;
    }
  }
}