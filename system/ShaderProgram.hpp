/*
 * ShaderProgram.hpp
 *
 *  Created on: Apr 10, 2012
 *      Author: sharav
 */

#ifndef SHADERPROGRAM_HPP_
#define SHADERPROGRAM_HPP_

#include "GL/glew.h"
#include <iostream>
#include <vector>
#include <map>
#include "Shader.hpp"

class ShaderProgram
{
public:
	ShaderProgram(std::string name);
	~ShaderProgram();

	void Activate();
	void Deactivate();

	void AttachShader(Shader *shader);
	void BindAttribute(GLuint index, std::string attrName);
	void link();

	inline GLuint GetID() const { return programID; }

	GLuint GetUniformLocation(const char* name) const;

	void SetUniform1f(const char* name, float v) const;
	void SetUniform2f(const char* name, float v0, float v1) const;
private:
	bool isLinked;
	std::vector<Shader *> shaders;
	GLuint programID;
	std::string programName;
	std::map<std::string, GLuint> attribs;
	bool isActive;
};


#endif /* SHADERPROGRAM_HPP_ */
