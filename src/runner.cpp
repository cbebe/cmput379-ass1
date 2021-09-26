#include <chrono>
#include <iostream>

int longlongJob(long long maxSeconds, long long num) {
  using std::chrono::high_resolution_clock;
  using std::chrono::seconds;
  seconds maxDuration(maxSeconds);

  auto start = high_resolution_clock::now();
  int k = 0;
  for (long long i = 0; i < num; i++)
    for (long long j = 0; j < num; j++) {
      if ((high_resolution_clock::now() - start) >= maxDuration) return k;

      k += 20;
    }

  return k;
}

int main(int argc, char const *argv[]) {
  long long maxSeconds;
  long long num;
  if (argc == 3) {
    maxSeconds = std::stoi(argv[1]);
    num = std::stoi(argv[2]);
  } else if (argc == 2) {
    maxSeconds = std::stoi(argv[1]);
    num = 200000000000;
  } else {
    std::cin >> maxSeconds >> num;
  }

  int result = longlongJob(maxSeconds, num);
  std::cout << result << std::endl;

  return 0;
}
