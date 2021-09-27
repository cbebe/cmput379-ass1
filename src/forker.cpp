#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

#define NUM_FORKS 3

int main() {
  int status;
  for (int f = 0; f < NUM_FORKS; f++) {
    int pid = fork();

    if (pid > 0) {
      wait(&status);
    } else if (pid < 0) {
      std::cerr << "fork failed" << std::endl;
      exit(1);
    } else {
      char* const args[] = {const_cast<char*>("./runner"),
                            const_cast<char*>("10"), nullptr};
      execvp(args[0], args);
    }
  }
}