#ifndef TIMER_HPP
#define TIMER_HPP

#include "global.hpp"

class Timer {
private:
	Timer();
	static double		_last;
	static double		_delta;

public:
	static void					Update(void);
	inline static double		GetDelta(void) { return (_delta); }
};

#endif