/*
 * Shader.hpp
 *
 *  Created on: Apr 10, 2012
 *      Author: sharavsambuu
 */

#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <iostream>
#include "GL/glew.h"


enum SHADERTYPE{VERTEX, FRAGMENT, GEOMETRY, TESSELATION};

class Shader
{
public:
	Shader(std::string name, SHADERTYPE type);
	~Shader();

	void Compile();
	void Load(std::string name);

	inline GLuint getShader() const { return shaderID; }

private:
	std::string name;
	std::string *source;
	bool        isCompiled;
	SHADERTYPE  shaderType;

	GLuint      shaderID;
};


#endif /* SHADER_HPP_ */
