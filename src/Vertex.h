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
	float getX();
	float getY();
	float getZ();
	bool operator!= (Vertex const &vert) const
	{
		return x != vert.x || y != vert.y || z != vert.z;
	}
};