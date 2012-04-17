/*
 * ObjModel.cpp
 *
 *  Created on: Apr 15, 2012
 *      Author: sharavsambuu
 */

#include "ObjModel.hpp"

ObjModel::ObjModel()
{
}
ObjModel::~ObjModel()
{
}

void ObjModel::Load(const char* filename) {

	std::ifstream in;
	in.open(filename);
	if (!in) {
		std::cerr << "could not open file " << filename << std::endl;
	}

	float x, y, z;
	unsigned int a[3], b[3];
	std::string line, word;
	std::vector<std::string> vec;
	std::vector<std::string>::iterator it;
	std::vector<normal> tempNormals;
	std::vector<unsigned int> list1;
	std::vector<unsigned int> list2;

	vertex dummy = vertex(0, 0, 0);
	vertices.push_back(dummy);
	tempNormals.push_back(dummy);

	// мөр мөрөөр нь унших
	while (getline(in, line)) {
		std::istringstream iss(line);
		vec.clear();
		while (iss >> word) {
			vec.push_back(word);
		}
		// файлын эхлэл
		it = vec.begin();

		iss.clear();
		iss.str(line);

		// vertex
		if (*it == "v") {
			iss >> word >> x >> y >> z;
			vertices.push_back(vertex(x, y, z));
		}
		// normal
		else if (*it == "vn") {
			iss >> word >> x >> y >> z;
			tempNormals.push_back(normal(x, y, z));
		}
		// face
		else if (*it == "f") {
			// f ийн дараа ирсэн тоонуудын жагсаалтыг хадгалах
			std::string numbers[3] = { *(++it), *(++it), *(++it) };

			// parse хийж тоонуудыг авах
			for (int i = 0; i < 3; i++) {
				iss.clear();
				iss.str(numbers[i]);
				vec.clear();
				// '/' тэмдэгтээр split хийх
				while (std::getline(iss, word, '/')) {
					vec.push_back(word);
				}
				// эхнийхийг авах
				iss.clear();
				iss.str(vec[0]);
				iss >> a[i];
				// текстур буулгалтын координат эсэхийг шалгах
				if (vec.size() == 3) {
					iss.clear();
					iss.str(vec[2]);
					iss >> b[i];
				}
				else {
					iss.clear();
					iss.str(vec[1]);
					iss >> b[i];
				}
			}
			faces.push_back(face(a[0], a[1], a[2]));

			list1.push_back(a[0]);
			list1.push_back(a[1]);
			list1.push_back(a[2]);
			list2.push_back(b[0]);
			list2.push_back(b[1]);
			list2.push_back(b[2]);
		}
	}
	// нормал утгуудыг хадгална
	normals = std::vector<normal>(vertices.size(), normal(0, 0, 0));
	// face-үүдийг эрэмбэлэх
	for (unsigned int i = 0; i < list1.size(); i++) {
		if (list1[i] != list2[i]) {
			normals[list1[i]] = tempNormals[list2[i]];
		} else {
			normals[list1[i]] = tempNormals[list1[i]];
		}
	}
	std::cout<<"Total faces    : "<<faces.size()<<"\n"
			 <<"Total vertices : "<<vertices.size()-1<<"\n"
			 <<"Total normals  : "<<normals.size()-1<<std::endl;
}

