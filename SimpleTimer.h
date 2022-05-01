#pragma once
#include <chrono>
#include <iostream>

class SimpleTimer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double_t> duraction;
public:
	SimpleTimer();
	~SimpleTimer();
	friend int32_t main();
	friend void timer_with_chrono();
};