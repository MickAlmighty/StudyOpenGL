#include "Triangle.h"
#include <iostream>

Triangle::Triangle(std::vector<Vertex> vector3): vec3(vector3)
{
	mids = std::vector<Vertex>();
	calculateMids();
}

Triangle::Triangle()
{
	
}

Triangle::Triangle(float vertices[])
{
	this->vec3 = std::vector<Vertex>();
	this->mids = std::vector<Vertex>();
	for(int i = 0; i < 9; i += 3)
	{
		float x = 0;
		float y = 0;
		float z = 0;
		for(int j = 0; j < 3; j++)
		{
			if( (i + j) % 3 == 0)
			{
				x = vertices[i + j];
			}
			if ((i + j) % 3 == 1)
			{
				y = vertices[i + j];
			}
			if ((i + j) % 3 == 2)
			{
				z = vertices[i + j];
			}
		}
		//std::cout <<"Wyswietl: "<< x << " " << y << " " << z << std::endl;
		//std::shared_ptr<Vertex> shared_ptr(new Vertex(x, y, z));
		vec3.push_back(Vertex(x,y,z));
	}
	calculateMids();
}


Triangle::~Triangle() { }

void Triangle::calculateMids()
{
	for(unsigned int i = 0; i < (vec3.size() - 1); i++)
	{
		for (unsigned int j = 1; j < vec3.size(); j++)
		{
			if(vec3.at(i) != vec3.at(j))
			{
				mids.push_back(createMidVertex(vec3.at(i), vec3.at(j)));
			}
		}
	}
}

Vertex Triangle::createMidVertex(Vertex &x1, Vertex &x2)
{
	float a1 = (x1.getX() + x2.getX()) / 2;
	float y1 = (x1.getY() + x2.getY()) / 2;
	float z1 = (x1.getZ() + x2.getZ()) / 2;
	return Vertex(a1, y1, z1);
}

std::vector<Vertex> Triangle::getVec3()
{
	return vec3;
}
std::vector<Vertex> Triangle::getMids()
{
	return mids;
}

