#include "SimpleTimer.h"

SimpleTimer::SimpleTimer() : duraction(std::chrono::nanoseconds(0)) {
	start = std::chrono::high_resolution_clock::now();
}

SimpleTimer::~SimpleTimer() {
	end = std::chrono::high_resolution_clock::now();
	duraction = end - start;

#ifdef COUT
	std::cout << "Времени прошло: " << duraction.count() << " секунд\n\n";
#endif
}