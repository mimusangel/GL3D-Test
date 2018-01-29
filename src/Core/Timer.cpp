#include "Timer.hpp"

double		Timer::_last = glfwGetTime();
double		Timer::_delta = 0.0;

void					Timer::Update(void)
{
	double now = glfwGetTime();
	_delta = now - _last;
	_last = now;
}