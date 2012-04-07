/*
 * LogManager.hpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#ifndef LOGMANAGER_HPP_
#define LOGMANAGER_HPP_

#include "../util/Singleton.hpp"

class LogManager : public Singleton<LogManager>
{
	friend class Singleton<LogManager>;
public:
	LogManager();
	~LogManager();

};

#endif /* LOGMANAGER_HPP_ */
