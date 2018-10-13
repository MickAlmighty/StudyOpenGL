#include "Vertex.h"
#include "Triangle.h"

class VertexManager
{
private:

	std::vector<unsigned int> *indexArray;
	std::vector<float> *floats;
	std::vector<Vertex*> *uniqueVertices;
	void VertexManager::insertThisValueToTheArray(Vertex* value);
public:
	VertexManager::VertexManager();
	VertexManager::~VertexManager();
	void VertexManager::createTrianglesFromVertexAndMids(int recursionLevel, std::vector<Vertex*> *, Triangle *);
	void VertexManager::createDataAndIndexArrays(std::vector<Vertex*> *vertices);
	std::vector<unsigned int>* VertexManager::getIndexArray();
	std::vector<float>* VertexManager::getFloats();
	std::vector<Vertex*>* VertexManager::getUniqueVertices();
};