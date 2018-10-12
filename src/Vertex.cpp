#include "Vertex.h"


Vertex::Vertex(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { };
Vertex::~Vertex()
{
	delete this;
}

float Vertex::getX()
{
	return this->x;
}
float Vertex::getY()
{
	return this->y;
};
float Vertex::getZ()
{
	return this->z;
};