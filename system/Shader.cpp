/*
 * Shader.cpp
 *
 *  Created on: Apr 10, 2012
 *      Author: sharavsambuu
 */

#include "Shader.hpp"
#include <fstream>

void printInfo(const GLuint &obj)
{
	GLint infologLength = 0;
	GLint charsWritten  = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infologLength);
	std::cerr<<"info log len "<<infologLength<<"\n";
	if(infologLength>0)
	{
		infoLog = new char[infologLength];
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);

		std::cerr<<infoLog<<std::endl;
		delete [] infoLog;
		glGetShaderiv(obj, GL_COMPILE_STATUS, &infologLength);
		if (infologLength==GL_FALSE)
		{
			std::cerr<<"shader compilation failed\n";
		}
	}
}



