/*
 * ShaderProgram.cpp
 *
 *  Created on: Apr 10, 2012
 *      Author: sharavsambuu
 */

#include "ShaderProgram.hpp"
#include "stdlib.h"

ShaderProgram::ShaderProgram(std::string name) {
	programID = glCreateProgram();
	std::cerr << "created program ID is " << programID << "\n";
	this->programName = name;
	isLinked = false;
	isActive = false;
}
ShaderProgram::~ShaderProgram() {
	std::cerr << "deleting shader program " << programName << "\n";
	glDeleteProgram(programID);
}

void ShaderProgram::Activate() {
	glUseProgram(programID);
	isActive = true;
}
void ShaderProgram::Deactivate() {
	isActive = false;
	glUseProgram(0);
}

void ShaderProgram::AttachShader(Shader *shader) {
	shaders.push_back(shader);
	glAttachShader(programID, shader->GetShader());
}

void ShaderProgram::BindAttribute(GLuint index, std::string attrName) {
	if (isLinked == true) {
		std::cerr << "warning binding attribute after link\n";
	}
	attribs[attrName] = index;
	glBindAttribLocation(programID, index, attrName.c_str());
	std::cerr << "bind attribute location " << programID << " index " << index
			<< " name " << attrName << "\n";
}

void ShaderProgram::Link() {
	glLinkProgram(programID);
	GLint infologLength = 0;
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength > 0) {
		char *infoLog = new char[infologLength];
		GLint charsWritten = 0;
		glGetProgramInfoLog(programID, infologLength, &charsWritten, infoLog);
		std::cerr << infoLog << std::endl;
		delete[] infoLog;
		glGetProgramiv(programID, GL_LINK_STATUS, &infologLength);
		if (infologLength == GL_FALSE) {
			std::cerr << "program linking failed and exiting\n";
			exit(EXIT_FAILURE);
		}
	}
	isLinked = true;
}

GLuint ShaderProgram::GetUniformLocation(const char* _name) const {
	GLint loc = glGetUniformLocation(programID, _name);
	if (loc == -1) {
		std::cerr << "Uniform \"" << _name << "\" not found in Program \""
				<< programName << "\"\n";
	}
	return loc;
}

//----------------------------------------------------------------------------------------------------------------------

void ShaderProgram::SetUniform1f(const char* _varname, float _v0) const {
	glUniform1f(GetUniformLocation(_varname), _v0);
}
void ShaderProgram::SetUniform2f(const char* _varname, float _v0,
		float _v1) const {
	glUniform2f(GetUniformLocation(_varname), _v0, _v1);
}
void ShaderProgram::SetUniform3f(const char* _varname, float _v0, float _v1,
		float _v2) const {
	glUniform3f(GetUniformLocation(_varname), _v0, _v1, _v2);
}
void ShaderProgram::SetUniform4f(const char* _varname, float _v0, float _v1,
		float _v2, float _v3) const {
	glUniform4f(GetUniformLocation(_varname), _v0, _v1, _v2, _v3);
}
void ShaderProgram::SetUniform1fv(const char* _varname, size_t _count,
		const float* _value) const {
	glUniform1fv(GetUniformLocation(_varname), _count, _value);
}
void ShaderProgram::SetUniform2fv(const char* _varname, size_t _count,
		const float* _value) const {
	glUniform2fv(GetUniformLocation(_varname), _count, _value);
}
void ShaderProgram::SetUniform3fv(const char* _varname, size_t _count,
		const float* _value) const {
	glUniform3fv(GetUniformLocation(_varname), _count, _value);
}
void ShaderProgram::SetUniform4fv(const char* _varname, size_t _count,
		const float* _value) const {
	glUniform4fv(GetUniformLocation(_varname), _count, _value);
}
void ShaderProgram::SetUniform1i(const char* _varname, GLint _v0) const {
	glUniform1i(GetUniformLocation(_varname), _v0);
}
void ShaderProgram::SetUniform2i(const char* _varname, GLint _v0,
		GLint _v1) const {
	glUniform2i(GetUniformLocation(_varname), _v0, _v1);
}
void ShaderProgram::SetUniform3i(const char* _varname, GLint _v0, GLint _v1,
		GLint _v2) const {
	glUniform3i(GetUniformLocation(_varname), _v0, _v1, _v2);
}
void ShaderProgram::SetUniform4i(const char* _varname, GLint _v0, GLint _v1,
		GLint _v2, GLint _v3) const {
	glUniform4i(GetUniformLocation(_varname), _v0, _v1, _v2, _v3);
}
void ShaderProgram::SetUniform1iv(const char* _varname, size_t _count,
		const GLint* _value) const {
	glUniform1iv(GetUniformLocation(_varname), _count, _value);
}
void ShaderProgram::SetUniform2iv(const char* _varname, size_t _count,
		const GLint* _value) const {
	glUniform2iv(GetUniformLocation(_varname), _count, _value);
}
void ShaderProgram::SetUniform3iv(const char* _varname, size_t _count,
		const GLint* _value) const {
	glUniform3iv(GetUniformLocation(_varname), _count, _value);
}
void ShaderProgram::SetUniform4iv(const char* _varname, size_t _count,
		const GLint* _value) const {
	glUniform4iv(GetUniformLocation(_varname), _count, _value);
}
void ShaderProgram::SetUniformMatrix2fv(const char* _varname, size_t _count,
		bool _transpose, const float* _value) const {
	glUniformMatrix2fv(GetUniformLocation(_varname), _count, _transpose,
			_value);
}
void ShaderProgram::SetUniformMatrix3fv(const char* _varname, size_t _count,
		bool _transpose, const float* _value) const {
	glUniformMatrix3fv(GetUniformLocation(_varname), _count, _transpose,
			_value);
}
void ShaderProgram::SetUniformMatrix4fv(const char* _varname, size_t _count,
		bool _transpose, const float* _value) const {
	glUniformMatrix4fv(GetUniformLocation(_varname), _count, _transpose,
			_value);
}
void ShaderProgram::SetUniformMatrix2x3fv(const char* _varname, size_t _count,
		bool _transpose, const float* _value) const {
	glUniformMatrix2x3fv(GetUniformLocation(_varname), _count, _transpose,
			_value);
}
void ShaderProgram::SetUniformMatrix2x4fv(const char* _varname, size_t _count,
		bool _transpose, const float* _value) const {
	glUniformMatrix2x4fv(GetUniformLocation(_varname), _count, _transpose,
			_value);
}
void ShaderProgram::SetUniformMatrix3x2fv(const char* _varname, size_t _count,
		bool _transpose, const float* _value) const {
	glUniformMatrix3x2fv(GetUniformLocation(_varname), _count, _transpose,
			_value);
}
void ShaderProgram::SetUniformMatrix3x4fv(const char* _varname, size_t _count,
		bool _transpose, const float* _value) const {
	glUniformMatrix3x4fv(GetUniformLocation(_varname), _count, _transpose,
			_value);
}
void ShaderProgram::SetUniformMatrix4x2fv(const char* _varname, size_t _count,
		bool _transpose, const float* _value) const {
	glUniformMatrix4x2fv(GetUniformLocation(_varname), _count, _transpose,
			_value);
}
void ShaderProgram::SetUniformMatrix4x3fv(const char* _varname, size_t _count,
		bool _transpose, const float* _value) const {
	glUniformMatrix4x3fv(GetUniformLocation(_varname), _count, _transpose,
			_value);
}
void ShaderProgram::GetUniformfv(const char* _varname, float* o_values) const {
	glGetUniformfv(programID, GetUniformLocation(_varname), o_values);
}
void ShaderProgram::GetUniformiv(const char* _varname,
		int32_t* o_values) const {
	glGetUniformiv(programID, GetUniformLocation(_varname), o_values);
}
void ShaderProgram::EnableAttribArray(const char* _name) const {
	std::map<std::string, GLuint>::const_iterator index = attribs.find(_name);
	if (index != attribs.end()) {
		std::cerr << "Enable attrib " << index->second << "\n";
		glEnableVertexAttribArray(index->second);
	}
}
void ShaderProgram::DisableAttribArray(const char* _name) const {
	glDisableVertexAttribArray(GetUniformLocation(_name));
}
bool ShaderProgram::VertexAttribPointer(const char* _name, GLint _size,
		GLenum _type, GLsizei _stride, const GLvoid *_data,
		bool _normalise) const {
	std::map<std::string, GLuint>::const_iterator attrib = attribs.find(
			_name);
	if (attrib != attribs.end()) {
		glVertexAttribPointer(attrib->second, _size, _type, _normalise, _stride,
				_data);
		return true;
	} else {
		return false;
	}
}
void ShaderProgram::VertexAttrib1f(const char * _name, GLfloat _v0) const {
	std::map<std::string, GLuint>::const_iterator attrib = attribs.find(
			_name);
	if (attrib != attribs.end()) {
		glVertexAttrib1f(attrib->second, _v0);
	}
}
void ShaderProgram::VertexAttrib2f(const char * _name, GLfloat _v0,
		GLfloat _v1) const {
	std::map<std::string, GLuint>::const_iterator attrib = attribs.find(
			_name);
	if (attrib != attribs.end()) {
		glVertexAttrib2f(attrib->second, _v0, _v1);
	}
}
void ShaderProgram::VertexAttrib3f(const char * _name, GLfloat _v0, GLfloat _v1,
		GLfloat _v2) const {
	std::map<std::string, GLuint>::const_iterator attrib = attribs.find(
			_name);
	if (attrib != attribs.end()) {
		glVertexAttrib3f(attrib->second, _v0, _v1, _v2);
	}
}
void ShaderProgram::VertexAttrib4f(const char * _name, GLfloat _v0, GLfloat _v1,
		GLfloat _v2, GLfloat _v3) const {
	std::map<std::string, GLuint>::const_iterator attrib = attribs.find(
			_name);
	if (attrib != attribs.end()) {
		glVertexAttrib4f(attrib->second, _v0, _v1, _v2, _v3);
	}
}
void ShaderProgram::VertexAttrib1fv(const char * _name,
		const GLfloat * _v) const {
	std::map<std::string, GLuint>::const_iterator attrib = attribs.find(
			_name);
	if (attrib != attribs.end()) {
		glVertexAttrib1fv(attrib->second, _v);
	}
}
void ShaderProgram::VertexAttrib2fv(const char * _name,
		const GLfloat * _v) const {
	std::map<std::string, GLuint>::const_iterator attrib = attribs.find(
			_name);
	if (attrib != attribs.end()) {
		glVertexAttrib2fv(attrib->second, _v);
	}
}
void ShaderProgram::VertexAttrib3fv(const char * _name,
		const GLfloat * _v) const {
	std::map<std::string, GLuint>::const_iterator attrib = attribs.find(
			_name);
	if (attrib != attribs.end()) {
		glVertexAttrib3fv(attrib->second, _v);
	}
}
void ShaderProgram::VertexAttrib4fv(const char * _name,
		const GLfloat * _v) const {
	std::map<std::string, GLuint>::const_iterator attrib = attribs.find(
			_name);
	if (attrib != attribs.end()) {
		glVertexAttrib4fv(attrib->second, _v);
	}
}
void ShaderProgram::VertexAttrib4iv(const char * _name,
		const GLint * _v) const {
	std::map<std::string, GLuint>::const_iterator attrib = attribs.find(
			_name);
	if (attrib != attribs.end()) {
		glVertexAttrib4iv(attrib->second, _v);
	}
}
void ShaderProgram::VertexAttrib4uiv(const char * _name,
		const GLuint * _v) const {
	std::map<std::string, GLuint>::const_iterator attrib = attribs.find(
			_name);
	if (attrib != attribs.end()) {
		glVertexAttrib4uiv(attrib->second, _v);
	}
}
void ShaderProgram::VertexAttrib4Niv(const char * _name,
		const GLint * _v) const {
	std::map<std::string, GLuint>::const_iterator attrib = attribs.find(
			_name);
	if (attrib != attribs.end()) {
		glVertexAttrib4Niv(attrib->second, _v);
	}
}
void ShaderProgram::VertexAttrib4Nuiv(const char * _name,
		const GLuint * _v) const {
	std::map<std::string, GLuint>::const_iterator attrib = attribs.find(
			_name);
	if (attrib != attribs.end()) {
		glVertexAttrib4Nuiv(attrib->second, _v);
	}
}
