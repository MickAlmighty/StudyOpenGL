#ifndef VERTEXMANAGER_H
#define VERTEXMANAGER_H


#include <Vertex.h>
#include "Triangle.h"
#include <Tetrahedron.h>

class VertexManager
{
private:
	std::vector<unsigned int> *indexArray;
	std::vector<float> *floats;
	std::vector<Vertex> *uniqueVertices;
	void VertexManager::insertThisValueToTheArray(Vertex &value);
	void VertexManager::addVertices(std::vector<Vertex>* allVertices, Triangle &triangle);
public:
	VertexManager::VertexManager();
	VertexManager::~VertexManager();
	void VertexManager::CreateTetrahedrons(int recursionLevel, std::vector<Tetrahedron> n_tetrahedrons, std::vector<Triangle> &triangles);
	void VertexManager::createTrianglesFromVertexAndMids(int recursionLevel, std::vector<Vertex> *, Triangle &);
	void VertexManager::createTetrahedron(int recursionLevel, std::vector<Vertex> *, std::vector<Triangle> &);
	void VertexManager::createDataAndIndexArrays(std::vector<Vertex> *vertices);
	void VertexManager::SummariseVertices(std::vector<Vertex>* , std::vector<Triangle>&);
	std::vector<unsigned int>* VertexManager::getIndexArray();
	std::vector<float>* VertexManager::getFloats();
	std::vector<Vertex>* VertexManager::getUniqueVertices();
};
#endif
