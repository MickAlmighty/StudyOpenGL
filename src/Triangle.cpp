#include "Triangle.h"
#include <iostream>

Triangle::Triangle(std::vector<Vertex*> *vector3): vec3(vector3)
{
	mids = new std::vector<Vertex*>();
	calculateMids();
}
Triangle::Triangle(float vertices[])
{
	this->vec3 = new std::vector<Vertex*>();
	this->mids = new std::vector<Vertex*>();
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
		std::cout <<"Wyswietl: "<< x << " " << y << " " << z << std::endl;
		vec3->push_back(new Vertex(x, y, z));
	}
	calculateMids();
}


Triangle::~Triangle()
{
	
}

void Triangle::calculateMids()
{
	for(unsigned int i = 0; i < (vec3->size() - 1); i++)
	{
		for (unsigned int j = 1; j < vec3->size(); j++)
		{
			if(vec3->at(i) != vec3->at(j))
			{
				this->mids->push_back(getMidVertices(vec3->at(i), vec3->at(j)));
			}
		}
	}
}

Vertex* Triangle::getMidVertices(Vertex *x1, Vertex *x2)
{
	float a1 = (x1->getX() + x2->getX()) / 2;
	float y1 = (x1->getY() + x2->getY()) / 2;
	float z1 = (x1->getZ() + x2->getZ()) / 2;
	return new Vertex(a1, y1, z1);
}

void Triangle::createTrianglesFromVertexAndMids(int recursionLevel, std::vector<Vertex*> *allVerticles, Triangle *n_triangle)
{
	if (recursionLevel > 0)
	{
		for (unsigned int i = 0; i < this->vec3->size(); i++)
		{
			if (i == 0)
			{
				std::vector<Vertex*> *n_vertices = new std::vector<Vertex*>();
				n_vertices->push_back(n_triangle->vec3->at(i));
				n_vertices->push_back(n_triangle->mids->at(0));
				n_vertices->push_back(n_triangle->mids->at(1));
				if(recursionLevel == 1)
				{
					allVerticles->push_back(n_triangle->vec3->at(i));
					allVerticles->push_back(n_triangle->mids->at(0));
					allVerticles->push_back(n_triangle->mids->at(1));
				}
				createTrianglesFromVertexAndMids(recursionLevel - 1, allVerticles, new Triangle(n_vertices));
			}
			if (i == 1)
			{
				std::vector<Vertex*> *n_vertices = new std::vector<Vertex*>();
				n_vertices->push_back(n_triangle->vec3->at(i));
				n_vertices->push_back(n_triangle->mids->at(0));
				n_vertices->push_back(n_triangle->mids->at(2));
				if(recursionLevel == 1)
				{
					allVerticles->push_back(n_triangle->vec3->at(i));
					allVerticles->push_back(n_triangle->mids->at(0));
					allVerticles->push_back(n_triangle->mids->at(2));
				}
				createTrianglesFromVertexAndMids(recursionLevel - 1, allVerticles, new Triangle(n_vertices));
			}
			if (i == 2)
			{
				std::vector<Vertex*> *n_vertices = new std::vector<Vertex*>();
				n_vertices->push_back(n_triangle->vec3->at(i));
				n_vertices->push_back(n_triangle->mids->at(1));
				n_vertices->push_back(n_triangle->mids->at(2));
				if(recursionLevel == 1)
				{
					allVerticles->push_back(n_triangle->vec3->at(i));
					allVerticles->push_back(n_triangle->mids->at(1));
					allVerticles->push_back(n_triangle->mids->at(2));
				}
				createTrianglesFromVertexAndMids(recursionLevel - 1, allVerticles, new Triangle(n_vertices));
			}
		}
	}
	
}

