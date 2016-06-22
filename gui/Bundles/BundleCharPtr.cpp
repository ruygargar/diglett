#include "BundleCharPtr.h"

#include <stddef.h>
#include <string.h>

BundleCharPtr::BundleCharPtr()
	: m_data(NULL)
{}

BundleCharPtr::~BundleCharPtr()
{
	if (m_data != NULL)
	{
		delete m_data;
	}
}

void BundleCharPtr::put(const char * text)
{
	if (m_data != NULL)
	{
		delete m_data;
	}

	m_data = new char[strlen(text)];
	strcpy(m_data, text);
}

char * BundleCharPtr::get()
{
	return m_data;
}