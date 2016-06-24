#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <stddef.h>

template <typename T>
	class Subject
{
	public:
		Subject();
		virtual ~Subject() {};

		void attach(Observer<T> * observer);
		void deattach();
		virtual void notify() = 0;

	protected:
		Observer<T> * m_observer;
};

template <typename T>
	Subject<T>::Subject()
{
	m_observer = NULL;
};

template <typename T>
	void Subject<T>::attach(Observer<T> * observer)
{
	m_observer = observer;
};

template <typename T>
	void Subject<T>::deattach()
{
	m_observer = NULL;
};

#endif // SUBJECT_H