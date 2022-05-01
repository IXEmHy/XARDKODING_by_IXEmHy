#include "SimpleTimer.h"

SimpleTimer::SimpleTimer()
{
	start = std::chrono::high_resolution_clock::now();
}


SimpleTimer::~SimpleTimer()
{
	end = std::chrono::high_resolution_clock::now();
	duraction = end - start;
	std::cout << "Ïðîøëî âðåìåíè: " << duraction.count() << " ñåêóíä\n\n";
}