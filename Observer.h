#ifndef OBSERVER_H
#define OBSERVER_H

#include <stddef.h>

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
	if (m_model != NULL)
	{
		m_model->attach(this);
	}
}

template <typename T>
	Observer<T>::~Observer()
{
	if (m_model != NULL)
	{
		m_model->deattach();
	}
}

template <typename T>
	void Observer<T>::connect()
{	
	if (m_model != NULL)
	{
		m_model->notify();
	}
}

#endif // OBSERVER_H