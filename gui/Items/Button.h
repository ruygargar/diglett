#ifndef BUTTON_H
#define BUTTON_H

#include "Controller.h"

class Button : public Controller
{
	public:
		Button();
		~Button();

		bool isPushed();

	private:
		void right() {};
		void left() {};
		void push();

	private:
		bool m_pushed;
};

#endif // BUTTON_H