#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Encoder.h"

#define ENCODER_STEPS_REDUCTION 4

class Controller
{
	public:
		Controller();
		~Controller();

		void control();

	private:
		virtual void right() = 0;
		virtual void left() = 0;
		virtual void push() = 0;

	private:
		Encoder * m_encoder;
		int8_t m_microsteps;

};

#endif // CONTROLLER_H