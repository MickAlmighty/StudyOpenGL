#pragma once
#include <vector> 
#include "Vertex.h"
#include <memory>

class Triangle
{
private:
	std::vector<std::shared_ptr<Vertex>> *vec3;
	std::vector<std::shared_ptr<Vertex>> *mids;
public:
	void Triangle::calculateMids();
	std::shared_ptr<Vertex> Triangle::createMidVertex(std::shared_ptr<Vertex>, std::shared_ptr<Vertex> );
	Triangle::Triangle(std::vector<std::shared_ptr<Vertex>> &v);
	Triangle::Triangle(float[]);
	Triangle::~Triangle();
	std::vector<std::shared_ptr<Vertex>>* Triangle::getVec3();
	std::vector<std::shared_ptr<Vertex>>* Triangle::getMids();
};
