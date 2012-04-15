/*
 * ObjModel.hpp
 *
 *  Created on: Apr 15, 2012
 *      Author: sharavsambuu
 */

#ifndef OBJMODEL_HPP_
#define OBJMODEL_HPP_

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

struct face
{
	unsigned int f1, f2, f3;
	face(unsigned int p1, unsigned int p2, unsigned int p3)
		: f1(p1), f2(p2), f3(p3) {}
};

struct vertex
{
	float x, y, z;
	vertex(float p1, float p2, float p3)
	: x(p1), y(p2), z(p3) {}
};

typedef vertex normal;

class ObjModel
{
public:
	ObjModel();
	~ObjModel();

	void Load(const char* filename);

	std::vector<vertex> vertices;
	std::vector<normal> normals;
	std::vector<face>   faces;
protected:
private:
};

#endif /* OBJMODEL_HPP_ */
