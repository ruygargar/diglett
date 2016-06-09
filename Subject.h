#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <stddef.h>

#include "Logger.h"

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
	logger_println("-> Subject<T>::Subject()");
	m_observer = NULL;
	logger_println("<- Subject<T>::Subject()");
};

template <typename T>
	void Subject<T>::attach(Observer<T> * observer)
{
	logger_println("-> Subject<T>::attach()");
	m_observer = observer;
	logger_println("<- Subject<T>::attach()");
};

template <typename T>
	void Subject<T>::deattach()
{
	logger_println("-> Subject<T>::deattach()");
	m_observer = NULL;
	logger_println("<- Subject<T>::deattach()");
};

#endif // SUBJECT_H