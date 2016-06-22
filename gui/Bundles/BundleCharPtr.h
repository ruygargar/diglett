#ifndef BUNDLE_CHAR_PTR_H
#define BUNDLE_CHAR_PTR_H

#include "BundleBase.h"

class BundleCharPtr : public BundleBase
{
	public:
		BundleCharPtr();
		~BundleCharPtr();

		void put(const char * text);
		char * get();

	private:
		char * m_data;
};

#endif // BUNDLE_CHAR_PTR_H