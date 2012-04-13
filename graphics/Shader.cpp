/*
 * Shader.cpp
 *
 *  Created on: Apr 10, 2012
 *      Author: sharavsambuu
 */

#include "Shader.hpp"
#include <fstream>
#include "stdlib.h"

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

Shader::Shader(std::string name, SHADERTYPE type)
{
	this->name = name;
	shaderType = type;
	isCompiled = false;
	switch(type)
	{
	case VERTEX     : { shaderID = glCreateShader(GL_VERTEX_SHADER  ); break; }
	case FRAGMENT   : { shaderID = glCreateShader(GL_FRAGMENT_SHADER); break; }
	case GEOMETRY   : { shaderID = glCreateShader(GL_GEOMETRY_SHADER); break;}
	case TESS_EVAL  : { shaderID = glCreateShader(GL_TESS_EVALUATION_SHADER); break;}
	case TESS_CNTRL : { shaderID = glCreateShader(GL_TESS_CONTROL_SHADER); break;}
	}
	source = 0;
}
Shader::~Shader()
{
	std::cerr<<"deleting shader "<<name<<"\n";
	delete source;
	glDeleteShader(shaderID);
}

void Shader::Compile()
{
	if (source==0)
	{
		std::cerr<<"Warning no shader source loaded\n";
		return;
	}
	glCompileShader(shaderID);
	printInfo(shaderID);
	isCompiled = true;
}

void Shader::Load(std::string name)
{
	if(source!=0)
	{
		delete source;
	}
	std::ifstream shaderSource(name.c_str());
	if (!shaderSource.is_open())
	{
		std::cerr<<"file not found "<<name.c_str()<<"\n";
		exit(EXIT_FAILURE);
	}
	source = new std::string(
			std::istreambuf_iterator<char>(shaderSource),
			std::istreambuf_iterator<char>()
			);
	shaderSource.close();
	*source += "\0";

	const char* data = source->c_str();
	glShaderSource(shaderID, 1, &data, NULL);
	isCompiled = false;
	std::cerr<<"Shader loaded and source attached\n";
	printInfo(shaderID);
}

