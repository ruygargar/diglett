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

		void attach(Observer<T> * observer, ObserverType type);
		void deattach(ObserverType type);
		virtual void notify() = 0;

	protected:
		Observer<T> * m_observer_gui;
		Observer<T> * m_observer_logger;
};

template <typename T>
	Subject<T>::Subject()
	: m_observer_gui(NULL)
	, m_observer_logger(NULL)
{}

template <typename T>
	void Subject<T>::attach(Observer<T> * observer, ObserverType type)
{
	switch (type)
	{
		case OBSERVER_GUI:
		{
			m_observer_gui = observer;
			break;
		}
		case OBSERVER_LOGGER:
		{
			m_observer_logger = observer;
			break;
		}
	}
};

template <typename T>
	void Subject<T>::deattach(ObserverType type)
{
	switch (type)
	{
		case OBSERVER_GUI:
		{
			m_observer_gui = NULL;
			break;
		}
		case OBSERVER_LOGGER:
		{
			m_observer_logger = NULL;
			break;
		}
	}
};

#endif // SUBJECT_H