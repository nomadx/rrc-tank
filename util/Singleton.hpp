/*
 * Singleton.hpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_
#include <stddef.h>
template <typename T> class Singleton
{
protected:
	static T* instance;

	Singleton(){}
	virtual ~Singleton(){}
public:
	static inline T& getInstance()
	{
		if (instance == NULL)
		{
			instance = new T;
		}
		return *instance;
	}
	static inline void killInstance()
	{
		if (instance != NULL)
		{
			delete instance;
		}
		instance = NULL;
	}
};

template <typename T> T* Singleton<T>::instance = NULL;

#endif /* SINGLETON_HPP_ */
