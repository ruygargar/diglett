#ifndef SCREEN_H
#define SCREEN_H

#include "StateMachine.h"
#include "BundleBase.h"

#include <stddef.h>

class Screen
{
	public:
		Screen() {};
		virtual ~Screen() {};
		virtual void control() = 0;
		virtual Event_t compute() = 0;
		virtual void draw() = 0;
		virtual BundleBase * saveContext() { return NULL; };
};

#endif // SCREEN_H