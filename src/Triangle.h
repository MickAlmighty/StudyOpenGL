#pragma once
#include <vector> 
#include "Vertex.h"
class Triangle
{
private:
	std::vector<Vertex*> *vec3;
	std::vector<Vertex*> *mids;
public:
	void Triangle::calculateMids();
	Vertex* Triangle::getMidVertices(Vertex*, Vertex*);
	Triangle::Triangle(std::vector<Vertex*> *v);
	Triangle::Triangle(float[]);
	Triangle::~Triangle();
	void Triangle::createTrianglesFromVertexAndMids(int, std::vector<Vertex*> *, Triangle *);
};
