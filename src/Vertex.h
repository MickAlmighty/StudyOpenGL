#pragma once

class Vertex
{
private:
	float x;
	float y;
	float z;
public:	
	Vertex::Vertex(float x, float y, float z);
	Vertex::~Vertex();
	float Vertex::getX();
	float Vertex::getY();
	float Vertex::getZ();
	bool operator!= (Vertex const &vertex) const
	{
		return x != vertex.x || y != vertex.y || z != vertex.z;
	}
	bool operator== (Vertex const &vertex) const
	{
		return x == vertex.x && y == vertex.y && z == vertex.z;
	}
};