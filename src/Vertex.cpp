#include "Vertex.h"


Vertex::Vertex(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { };
Vertex::~Vertex() { };

float Vertex::getX()
{
	return x;
}
float Vertex::getY()
{
	return y;
};
float Vertex::getZ()
{
	return z;
};