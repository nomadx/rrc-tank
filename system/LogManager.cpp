/*
 * LogManager.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: sharavsambuu
 */

#include "LogManager.hpp"

LogManager::LogManager()
{
}

LogManager::~LogManager()
{
	 out<< "\nLogging ended.";
	 out.close();
}

void LogManager::Init(char* filename)
{
	std::fstream temp(filename, std::ios_base::in);
	std::fstream backup(std::string(std::string(filename).append(".backup")).c_str(), std::ios_base::out | std::ios_base::trunc);
	temp.seekg(0,std::ios::end);
	int length = temp.tellg();
	temp.seekg(0,std::ios::beg);
	char* buffer = new char[length];
	temp.read(buffer,length);
	backup.write(buffer, length-4);
	delete[] buffer;
	temp.close();
	backup.close();
	out.open(filename, std::ios_base::out | std::ios_base::trunc);
	char date[9];
	_strdate(date);
	out<< "Log file started on (mm/dd/year) " << date << "\n\n";
}

void LogManager::Log(std::string message)
{
	out<<message<<"\n";
}
