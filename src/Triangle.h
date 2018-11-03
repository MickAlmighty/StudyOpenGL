#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector> 
#include "Vertex.h"

class Triangle
{
private:
	std::vector<Vertex> vec3;
	std::vector<Vertex> mids;
public:
	void Triangle::calculateMids();
	Vertex Triangle::createMidVertex(Vertex &, Vertex &);
	Triangle::Triangle(std::vector<Vertex> v);
	Triangle::Triangle(float[]);
	Triangle::Triangle();
	Triangle::~Triangle();
	std::vector<Vertex> Triangle::getVec3();
	std::vector<Vertex> Triangle::getMids();
};
#endif
