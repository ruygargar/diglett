#include "Controller.h"

Controller::Controller()
	: m_microsteps(0)
{
	m_encoder = new Encoder();
}

Controller::~Controller()
{
	delete m_encoder;
}

void Controller::control()
{
	int16_t movement = m_encoder->getMovement() + m_microsteps;
	int16_t movement_steps = movement / ENCODER_STEPS_REDUCTION;
	int16_t movement_microsteps = movement % ENCODER_STEPS_REDUCTION;

	m_microsteps = movement_microsteps;

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

	if (pushed != 0)
	{
		push();
	}
}