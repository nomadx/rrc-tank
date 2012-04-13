/*
 * LogManager.hpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#ifndef LOGMANAGER_HPP_
#define LOGMANAGER_HPP_

#include "../util/Singleton.hpp"
#include <string>
#include <fstream>
#include <time.h>

class LogManager : public Singleton<LogManager>
{
	friend class Singleton<LogManager>;
public:
	LogManager();
	~LogManager();

	void Init(char* filename);
	void Log(std::string message);

private:
};

#endif /* LOGMANAGER_HPP_ */
