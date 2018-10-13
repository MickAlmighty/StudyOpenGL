#include "VertexManager.h"

VertexManager::VertexManager()
{
	floats = new std::vector<float>();
	indexArray = new std::vector<unsigned int>();
	uniqueVertices = new std::vector<Vertex*>();
}

VertexManager::~VertexManager()
{
	
}


void VertexManager::createTrianglesFromVertexAndMids(int recursionLevel, std::vector<Vertex*> *allVertices, Triangle *n_triangle)
{
	if (recursionLevel > 0)
	{
		for (unsigned int i = 0; i < n_triangle->getVec3()->size(); i++)
		{
			if (i == 0)
			{
				std::vector<Vertex*> *n_vertices = new std::vector<Vertex*>();
				n_vertices->push_back(n_triangle->getVec3()->at(i));
				n_vertices->push_back(n_triangle->getMids()->at(0));
				n_vertices->push_back(n_triangle->getMids()->at(1));
				if (recursionLevel == 1)
				{
					allVertices->push_back(n_triangle->getVec3()->at(i));
					allVertices->push_back(n_triangle->getMids()->at(0));
					allVertices->push_back(n_triangle->getMids()->at(1));
				}
				Triangle *tmpTriangle = new Triangle(n_vertices);
				createTrianglesFromVertexAndMids(recursionLevel - 1, allVertices, tmpTriangle);
				delete tmpTriangle;

			}
			if (i == 1)
			{
				std::vector<Vertex*> *n_vertices = new std::vector<Vertex*>();
				n_vertices->push_back(n_triangle->getVec3()->at(i));
				n_vertices->push_back(n_triangle->getMids()->at(0));
				n_vertices->push_back(n_triangle->getMids()->at(2));
				if (recursionLevel == 1)
				{
					allVertices->push_back(n_triangle->getVec3()->at(i));
					allVertices->push_back(n_triangle->getMids()->at(0));
					allVertices->push_back(n_triangle->getMids()->at(2));
				}
				Triangle *tmpTriangle = new Triangle(n_vertices);
				createTrianglesFromVertexAndMids(recursionLevel - 1, allVertices, tmpTriangle);
				delete tmpTriangle;
			}
			if (i == 2)
			{
				std::vector<Vertex*> *n_vertices = new std::vector<Vertex*>();
				n_vertices->push_back(n_triangle->getVec3()->at(i));
				n_vertices->push_back(n_triangle->getMids()->at(1));
				n_vertices->push_back(n_triangle->getMids()->at(2));
				if (recursionLevel == 1)
				{
					allVertices->push_back(n_triangle->getVec3()->at(i));
					allVertices->push_back(n_triangle->getMids()->at(1));
					allVertices->push_back(n_triangle->getMids()->at(2));
				}
				Triangle *tmpTriangle = new Triangle(n_vertices);
				createTrianglesFromVertexAndMids(recursionLevel - 1, allVertices, tmpTriangle);
				delete tmpTriangle;
			}
			
		}
	}
}

void VertexManager::createDataAndIndexArrays(std::vector<Vertex*> *vertices)
{
	floats->clear();
	indexArray->clear();
	uniqueVertices->clear();
	
	for (Vertex* element : *vertices)
	{
		insertThisValueToTheArray(element);
	}
	for (Vertex* element : *uniqueVertices)
	{
		floats->push_back(element->getX());
		floats->push_back(element->getY());
		floats->push_back(element->getZ());
	}
}

void VertexManager::insertThisValueToTheArray(Vertex* vertex)
{
	auto it = std::find(uniqueVertices->begin(), uniqueVertices->end(), vertex);
	if(it != uniqueVertices->end())
	{
		int index = std::distance(uniqueVertices->begin(), it);
		indexArray->push_back(index);
	}
	else
	{
		uniqueVertices->push_back(vertex);
		indexArray->push_back(uniqueVertices->size() - 1);
	}
}

std::vector<unsigned int>* VertexManager::getIndexArray()
{
	return indexArray;
}
std::vector<float>* VertexManager::getFloats()
{
	return floats;
}
std::vector<Vertex*>* VertexManager::getUniqueVertices()
{
	return uniqueVertices;
}