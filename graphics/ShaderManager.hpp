/*
 * ShaderManager.hpp
 *
 *  Created on: Apr 10, 2012
 *      Author: sharavsambuu
 */

#ifndef SHADERMANAGER_HPP_
#define SHADERMANAGER_HPP_

#include "../util/Singleton.hpp"
#include "GL/glew.h"
#include <iostream>
#include <vector>
#include <map>
#include "Shader.hpp"
#include "ShaderProgram.hpp"

class ShaderManager: public Singleton<ShaderManager> {
	friend class Singleton<ShaderManager> ;
public:
	ShaderManager();
	~ShaderManager();

	bool LinkShader(std::string name);
	void CreateShaderProgram(std::string name);
	void AttachShader(std::string name, SHADERTYPE type);
	void AttachShaderToProgram(std::string program, std::string shader);
	GLuint GetProgramID(std::string name);
	void CompileShader(std::string name);
	void LinkProgramObject(std::string name);
	void Use(std::string name);
	void BindAttribute(std::string programName, GLuint index, std::string attribName);
	void LoadShaderSource(std::string shaderName, std::string sourceFile);
	ShaderProgram * operator[](const std::string &programName);
private:
	std::map<std::string, ShaderProgram *> shaderPrograms;
	std::map<std::string, Shader *> shaders;
};

#endif /* SHADERMANAGER_HPP_ */
