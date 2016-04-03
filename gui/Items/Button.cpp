#include "Button.h"

Button::Button()
	: m_pushed(false)
{}

Button::~Button() {}

bool Button::isPushed()
{
	return m_pushed;
}

void Button::push()
{
	m_pushed = true;
}