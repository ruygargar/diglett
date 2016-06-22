#ifndef SITE_SCREEN_H
#define SITE_SCREEN_H

#include "Screen.h"
#include "BundleCharPtr.h"

#include "Text.h"
#include "Textbox.h"
#include "Spinner.h"

class SiteScreen : public Screen
{
	public:
		SiteScreen();
		~SiteScreen();

		void control();
		Event_t compute();
		void draw();

		BundleCharPtr * saveContext();

	private:
		Text * m_text;
		Textbox * m_textbox;
		Spinner * m_spinner;
};

#endif // SITE_SCREEN_H