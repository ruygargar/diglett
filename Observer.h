#ifndef OBSERVER_H
#define OBSERVER_H

#include <stddef.h>

#include "Logger.h"

template <typename T> class Subject;

template <typename T>
	class Observer
{
	public:
		Observer(Subject<T> * model);
		virtual ~Observer();
		virtual void update(T value) = 0;
		void connect();

	protected:
		Subject<T> * m_model;
};

#include "Subject.h"

template <typename T>
	Observer<T>::Observer(Subject<T> * model)
	: m_model(model)
{
	logger_println("-> Observer<T>::Observer()");
	if (m_model != NULL)
	{
		m_model->attach(this);
	}
	logger_println("<- Observer<T>::Observer()");
}

template <typename T>
	Observer<T>::~Observer()
{
	logger_println("-> Observer<T>::~Observer()");
	if (m_model != NULL)
	{
		m_model->deattach();
	}
	logger_println("<- Observer<T>::~Observer()");
}

template <typename T>
	void Observer<T>::connect()
{
	logger_println("-> Observer<T>::connect()");	
	if (m_model != NULL)
	{
		m_model->notify();
	}
	logger_println("<- Observer<T>::connect()");
}

#endif // OBSERVER_H