#ifndef OBSERVER_H
#define OBSERVER_H

#include <stddef.h>

template <typename T> class Subject;

typedef enum
{
	OBSERVER_GUI,
	OBSERVER_LOGGER
} ObserverType;

template <typename T>
	class Observer
{
	public:
		Observer(Subject<T> * model, ObserverType type);
		virtual ~Observer();
		virtual void update(T value) = 0;
		void connect();

	protected:
		Subject<T> * m_model;
		ObserverType m_type;
};

#include "Subject.h"

template <typename T>
	Observer<T>::Observer(Subject<T> * model, ObserverType type)
	: m_model(model)
	, m_type(type)
{
	if (m_model != NULL)
	{
		m_model->attach(this, m_type);
	}
}

template <typename T>
	Observer<T>::~Observer()
{
	if (m_model != NULL)
	{
		m_model->deattach(m_type);
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