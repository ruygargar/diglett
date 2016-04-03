#ifndef SCREEN_H
#define SCREEN_H

#include "StateMachine.h"

class Screen
{
	public:
		virtual void control() = 0;
		virtual Event_t compute() = 0;
		virtual void draw() = 0;
};

#endif // SCREEN_H