#include <stdio.h>

// end the execution of shell379
void exit() {

    // wait until all processes are initiated by the shell are complete

    // print out the total user and system time for all processes run by the shell
}

void jobs() {
    // display the status of all running processes spawned by shell379
}

void kill(int pid) {
    // kill process pid
}

void resume(int pid) {
    // resume process pid. this undoes a suspend
}

void suspend(int pid) {
    // suspend execution of process pid. a resume will awaken it
}

void sleep(int seconds) {
    // sleep for given seconds
}

void execute(char* cmd, char** arg) {
    // spawn process to execute command with 0 or more arguments
}

// special arguments
// & - last argument - must run in background
// <fname - take input from a file named fname
// >fname - print output to a file named fname


int main() {
    
}
