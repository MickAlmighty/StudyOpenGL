#include "Vertex.h"
#include "Triangle.h"

class VertexManager
{
private:
	std::vector<unsigned int> *indexArray;
	std::vector<float> *floats;
	std::vector<std::shared_ptr<Vertex>> *uniqueVertices;
	void VertexManager::insertThisValueToTheArray(std::shared_ptr<Vertex> value);
public:
	VertexManager::VertexManager();
	VertexManager::~VertexManager();
	void VertexManager::createTrianglesFromVertexAndMids(int recursionLevel, std::vector<std::shared_ptr<Vertex>> *, Triangle &);
	void VertexManager::createDataAndIndexArrays(std::vector<std::shared_ptr<Vertex>> *vertices);
	std::vector<unsigned int>* VertexManager::getIndexArray();
	std::vector<float>* VertexManager::getFloats();
	std::vector<std::shared_ptr<Vertex>>* VertexManager::getUniqueVertices();
};