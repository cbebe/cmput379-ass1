#include <unistd.h>

#include <iostream>

void
printUsage (char const *name)
{
  std::cout << "USAGE: " << name << " <seconds>" << std::endl;
}

int
getInt (char const *name, char const *integer)
{
  try
    {
      int seconds = std::stoi (integer);
      if (seconds < 0)
        throw std::invalid_argument ("Must be a positive integer");

      return seconds;
    }
  catch (std::invalid_argument &e)
    {
      printUsage (name);
      exit (1);
    }
}
int
main (int argc, char const *argv[])
{
  if (argc != 2)
    {
      printUsage (argv[0]);
      exit (1);
    }

  sleep (getInt (argv[0], argv[1]));

  return 0;
}
