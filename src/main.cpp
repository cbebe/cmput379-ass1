#include <iostream>
#include <string>

void printPrompt()
{
  std::cout << "shell379> " << std::flush;
}

int main(int argc, char *argv[])
{
  while (true)
  {
    printPrompt();
    std::string input;
    std::cin >> input;
    std::cout << input << std::endl;
  }
}