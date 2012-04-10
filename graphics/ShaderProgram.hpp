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

class ShaderProgram {
public:
	ShaderProgram(std::string name);
	~ShaderProgram();

	void Activate();
	void Deactivate();

	void AttachShader(Shader *shader);
	void BindAttribute(GLuint index, std::string attrName);
	void Link();

	inline GLuint GetID() const {
		return programID;
	}

	GLuint GetUniformLocation(const char* name) const;

	void SetUniform1f(const char* _varname, float __v0) const;
	void SetUniform2f(const char* _varname, float _v0, float _v1) const;
	void SetUniform3f(const char* _varname, float _v0, float _v1, float _v2) const;
	void SetUniform4f(const char* _varname, float _v0, float _v1, float _v2, float _v3) const;
	void SetUniform1fv(const char* _varname, size_t _count, const float* _value) const;
	void SetUniform2fv(const char* _varname, size_t _count, const float* _value) const;
	void SetUniform3fv(const char* _varname, size_t _count,	const float* _value) const;
	void SetUniform4fv(const char* _varname, size_t _count,	const float* _value) const;
	void SetUniform1i(const char* _varname, GLint _v0) const;
	void SetUniform2i(const char* _varname, GLint _v0, GLint _v1) const;
	void SetUniform3i(const char* _varname, GLint _v0, GLint _v1, GLint _v2) const;
	void SetUniform4i(const char* _varname, GLint _v0, GLint _v1, GLint _v2, GLint _v3) const;
	void SetUniform1iv(const char* _varname, size_t _count,	const GLint* _value) const;
	void SetUniform2iv(const char* _varname, size_t _count,	const GLint* _value) const;
	void SetUniform3iv(const char* _varname, size_t _count, const GLint* _value) const;
	void SetUniform4iv(const char* _varname, size_t _count,	const GLint* _value) const;
	void SetUniformMatrix2fv(const char* _varname, size_t _count, bool _transpose, const float* _value) const;
	void SetUniformMatrix3fv(const char* _varname, size_t _count, bool _transpose, const float* _value) const;
	void SetUniformMatrix4fv(const char* _varname, size_t _count, bool _transpose, const float* _value) const;
	void SetUniformMatrix2x3fv(const char* _varname, size_t _count,	bool _transpose, const float* _value) const;
	void SetUniformMatrix2x4fv(const char* _varname, size_t _count,	bool _transpose, const float* _value) const;
	void SetUniformMatrix3x2fv(const char* _varname, size_t _count,	bool _transpose, const float* _value) const;
	void SetUniformMatrix3x4fv(const char* _varname, size_t _count, bool _transpose, const float* _value) const;
	void SetUniformMatrix4x2fv(const char* _varname, size_t _count, bool _transpose, const float* _value) const;
	void SetUniformMatrix4x3fv(const char* _varname, size_t _count,	bool _transpose, const float* _value) const;
	void GetUniformfv(const char* _name, float* o_values) const;
	void GetUniformiv(const char* _name, int32_t* o_values) const;

	void EnableAttribArray(const char* _name) const;
	void DisableAttribArray(const char* _name) const;

	bool VertexAttribPointer(const char* _name, GLint _size, GLenum _type, GLsizei _stride, const GLvoid *_data, bool _normalise = GL_FALSE) const;
	void VertexAttrib1f(const char * _name, GLfloat _v0) const;
	void VertexAttrib2f(const char * _name, GLfloat _v0, GLfloat _v1) const;
	void VertexAttrib3f(const char * _name, GLfloat _v0, GLfloat _v1, GLfloat _v2) const;
	void VertexAttrib4f(const char * _name, GLfloat _v0, GLfloat _v1, GLfloat _v2, GLfloat _v3) const;
	void VertexAttrib1fv(const char * _name, const GLfloat * _v) const;
	void VertexAttrib2fv(const char * _name, const GLfloat * _v) const;
	void VertexAttrib3fv(const char * _name, const GLfloat * _v) const;
	void VertexAttrib4fv(const char * _name, const GLfloat * _v) const;
	void VertexAttrib4iv(const char * _name, const GLint * _v) const;
	void VertexAttrib4uiv(const char * _name, const GLuint * _v) const;
	void VertexAttrib4Niv(const char * _name, const GLint * _v) const;
	void VertexAttrib4Nuiv(const char * _name, const GLuint * _v) const;
private:
	bool isLinked;
	std::vector<Shader *> shaders;
	GLuint programID;
	std::string programName;
	std::map<std::string, GLuint> attribs;
	bool isActive;
};

#endif /* SHADERPROGRAM_HPP_ */
