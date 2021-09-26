#include <iostream>
#include <chrono>
#include <sys/resource.h>

void longlongJob(long long maxSeconds, long long num)
{
	using namespace std::chrono;
	seconds maxDuration(maxSeconds);

	auto start = high_resolution_clock::now();
	int k = 0;
	for (long long i = 0; i < num; i++)
		for (long long j = 0; j < num; j++)
		{
			if ((high_resolution_clock::now() - start) >= maxDuration)
				return;
			k += 20;
		}
}

int main()
{
	long long maxSeconds;
	long long num;
	std::cin >> maxSeconds >> num;

	struct rusage usage;

	longlongJob(maxSeconds, num);

	getrusage(RUSAGE_SELF, &usage);

	std::cout << usage.ru_utime.tv_sec << std::endl;
	std::cout << usage.ru_stime.tv_sec << std::endl;

	return 0;
}
