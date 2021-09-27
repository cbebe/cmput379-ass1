#include <unistd.h>

#include <iostream>

void printUsage(char const* name) {
  std::cerr << "USAGE: " << name << " <seconds>" << std::endl;
}

void die(char const* name) {
  printUsage(name);
  exit(1);
}

int getInt(char const* name, char const* integer) {
  try {
    int seconds = std::stoi(integer);
    if (seconds < 0) {
      throw "Must be a positive integer";
    }

    return seconds;
  } catch (std::invalid_argument& e) {
    die(name);
  } catch (std::out_of_range& e) {
    die(name);
  } catch (const char* e) {
    die(name);
  }

  return 0;  // ??
}
int main(int argc, char const* argv[]) {
  if (argc != 2) {
    die(argv[0]);
  }

  sleep(getInt(argv[0], argv[1]));

  return 0;
}
