#include "Controller.h"

#include "Logger.h"

Controller::Controller()
	: m_microsteps(0)
{
	logger_println("-> Controller()");
	m_encoder = new Encoder();
	logger_println("<- Controller()");
}

Controller::~Controller()
{
	logger_println("-> ~Controller()");
	delete m_encoder;
	logger_println("<- ~Controller()");
}

void Controller::control()
{
	logger_println("-> Controller::control()");

	int16_t movement = m_encoder->getMovement();
	int16_t movement_steps = movement / ENCODER_STEPS_REDUCTION;
	int16_t movement_microsteps = movement % ENCODER_STEPS_REDUCTION;
	bool pushed = m_encoder->getClick();

	if (movement_steps > 0)
	{
		while (movement_steps > 0)
		{
			right();
			movement_steps--;
		}
	}

	if (movement_steps < 0)
	{
		while (movement_steps < 0)
		{
			left();
			movement_steps++;
		}
	}

	m_microsteps = movement_microsteps;

	if (pushed != 0)
	{
		push();
	}
	logger_println("<- Controller::control()");
}