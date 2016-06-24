#include "SiteScreen.h"

#include "LiquidCrystal.h"
extern LiquidCrystal lcd;

SiteScreen::SiteScreen()
{
	m_text = new Text(0, 0, "Nombre de la obra:\0");
	m_textbox = new Textbox(1);
	m_spinner = new Spinner(3, SPINNERTYPE_ALPHANUMERIC);
}

SiteScreen::~SiteScreen()
{
	delete m_text;
	delete m_textbox;
	delete m_spinner;
}

void SiteScreen::control()
{
	m_spinner->control();
}

Event_t SiteScreen::compute()
{
	char spinner_char = m_spinner->character();

	if (spinner_char == 0x7E)
	{
		return EVENT_NEXT_PAGE;
	}

	if (spinner_char == 0x00)
	{ }
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

void SiteScreen::draw()
{
	lcd.clear();
	m_text->draw();
	m_textbox->draw();
	m_spinner->draw();
}

BundleCharPtr * SiteScreen::saveContext()
{
	BundleCharPtr * bundle = new BundleCharPtr();
	bundle->put(m_textbox->text());
	return bundle;
}