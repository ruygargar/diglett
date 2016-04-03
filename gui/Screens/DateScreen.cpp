#include "DateScreen.h"

#include "LiquidCrystal.h"
extern LiquidCrystal lcd;

DateScreen::DateScreen()
{
	m_text = new Text(0, 0, "Fecha y hora:\0");
	m_textbox = new Textbox(1);
	m_spinner = new Spinner(3, SPINNERTYPE_NUMERIC);
}

DateScreen::~DateScreen()
{
	delete m_textbox;
	delete m_spinner;
}

void DateScreen::control()
{
	m_spinner->control();
}

Event_t DateScreen::compute()
{
	char spinner_char = m_spinner->character();

	if (spinner_char == 0x7E)
	{
		return EVENT_NEXT_PAGE;
	}

	if (spinner_char == 0x00)
	{}
	else if (spinner_char == 0x7F)
	{
		m_textbox->popChar();
	}
	else
	{
		m_textbox->pushChar(spinner_char);
	}

	return EVENT_NONE;
}

void DateScreen::draw()
{
	lcd.clear();
	m_text->draw();
	m_textbox->draw();
	m_spinner->draw();
}