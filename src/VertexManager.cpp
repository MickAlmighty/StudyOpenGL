#include <VertexManager.h>
#include "glm/detail/type_vec1.hpp"
#include <math.h>

VertexManager::VertexManager()
{
	floats = new std::vector<float>();
	indexArray = new std::vector<unsigned int>();
	uniqueVertices = new std::vector<Vertex>();
}

VertexManager::~VertexManager()
{
	
}

void VertexManager::createTetrahedron(int recursionLevel, std::vector<Vertex> *allVertices, std::vector<Triangle> &triangles)
{
	for (Triangle &triangle : triangles)
	{
		createTrianglesFromVertexAndMids(recursionLevel, allVertices, triangle);
	}
}
void VertexManager::CreateTetrahedrons(int recursionLevel, std::vector<Tetrahedron> n_tetrahedrons, std::vector<Triangle> &triangles)
{
	std::vector<Tetrahedron> tetrahedrons;
	std::vector<Triangle> all_triangles;
	std::vector<Vertex> n_vertices;

	/*for(int i = 0; i < recursionCounter; i++)
	{
		largeOffset /= 2;
		littleOffset /= 2;
	}*/
	if (recursionLevel > 0)
	{
		for (unsigned int i = 0; i < n_tetrahedrons.size(); i++)
		{
			if (recursionLevel == 1)
			{

				for (Triangle triangle : n_tetrahedrons.at(i).getTriangles())
				{
					triangles.push_back(triangle);
				}

			}
			else
			{
				float largeOffset = sqrt(pow(n_tetrahedrons.at(0).getTriangles().at(0).getVec3().at(0).getX() - n_tetrahedrons.at(0).getTriangles().at(0).getVec3().at(1).getX(), 2)
					+ pow(n_tetrahedrons.at(0).getTriangles().at(0).getVec3().at(0).getY() - n_tetrahedrons.at(0).getTriangles().at(0).getVec3().at(1).getY(), 2)
					+ pow(n_tetrahedrons.at(0).getTriangles().at(0).getVec3().at(0).getZ() - n_tetrahedrons.at(0).getTriangles().at(0).getVec3().at(1).getZ(), 2)) / 2;
				float littleOffset = largeOffset / 2;
				for (Triangle &n_triangle : n_tetrahedrons.at(i).getTriangles())//4 trójk¹ty
				{
					//lewy dolny wierzcho³ek
					n_vertices.push_back(n_triangle.getVec3().at(0));
					n_vertices.push_back(n_triangle.getMids().at(0));
					n_vertices.push_back(n_triangle.getMids().at(1));
					all_triangles.push_back(Triangle(n_vertices));
					n_vertices.clear();

					//prawy dolny wierzcho³ek
					n_vertices.push_back(n_triangle.getMids().at(0));
					n_vertices.push_back(n_triangle.getVec3().at(1));
					n_vertices.push_back(n_triangle.getMids().at(2));

					all_triangles.push_back(Triangle(n_vertices));
					n_vertices.clear();


					//gorny wierzcho³ek
					n_vertices.push_back(n_triangle.getMids().at(1));
					n_vertices.push_back(n_triangle.getVec3().at(2));
					n_vertices.push_back(n_triangle.getMids().at(2));

					all_triangles.push_back(Triangle(n_vertices));
					n_vertices.clear();

				}

				std::vector<Triangle> t_triangles = n_tetrahedrons.at(i).getTriangles();
				//wewnetrzna czesc lewego tetrahedronu
				n_vertices.push_back(t_triangles.at(0).getMids().at(0));
				n_vertices.push_back(t_triangles.at(0).getMids().at(1));
				n_vertices.push_back(t_triangles.at(1).getMids().at(0));
				all_triangles.push_back(Triangle(n_vertices));
				n_vertices.clear();

				std::vector<Triangle> tetrahedronParts;

				//lewy z przodu tetrahedron
				{
					tetrahedronParts.push_back(all_triangles.at(0));
					tetrahedronParts.push_back(all_triangles.at(3));
					tetrahedronParts.push_back(all_triangles.at(12));
					tetrahedronParts.push_back(all_triangles.at(9));
					tetrahedrons.push_back(Tetrahedron(tetrahedronParts));
					tetrahedronParts.clear();
				}
				CreateTetrahedrons(recursionLevel - 1, tetrahedrons, triangles);
				std::vector<Tetrahedron> otherTetrahedrons;
				//***********************
				//tetrahedron przesuniêty w prawo
				std::vector<Vertex> vertices;
				std::vector<Triangle> movedTriangles;
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						vertices.push_back(Vertex(tetrahedrons.at(0).getTriangles().at(j).getVec3().at(k).getX() + largeOffset,
							tetrahedrons.at(0).getTriangles().at(j).getVec3().at(k).getY(),
							tetrahedrons.at(0).getTriangles().at(j).getVec3().at(k).getZ()));

					}
					movedTriangles.push_back(Triangle(vertices));
					vertices.clear();
				}
				otherTetrahedrons.push_back(Tetrahedron(movedTriangles));
				CreateTetrahedrons(recursionLevel - 1, otherTetrahedrons, triangles);
				otherTetrahedrons.clear();
				movedTriangles.clear();
				//Tetrahedron przesuniêty do ty³u
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						vertices.push_back(Vertex(tetrahedrons.at(0).getTriangles().at(j).getVec3().at(k).getX() + littleOffset,
							tetrahedrons.at(0).getTriangles().at(j).getVec3().at(k).getY(),
							tetrahedrons.at(0).getTriangles().at(j).getVec3().at(k).getZ() - largeOffset));

					}
					movedTriangles.push_back(Triangle(vertices));
					vertices.clear();
				}
				otherTetrahedrons.push_back(Tetrahedron(movedTriangles));
				CreateTetrahedrons(recursionLevel - 1, otherTetrahedrons, triangles);
				otherTetrahedrons.clear();
				movedTriangles.clear();


				//Tetrahedron przesuniêty do gory
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						vertices.push_back(Vertex(tetrahedrons.at(0).getTriangles().at(j).getVec3().at(k).getX() + littleOffset,
							tetrahedrons.at(0).getTriangles().at(j).getVec3().at(k).getY() + largeOffset,
							tetrahedrons.at(0).getTriangles().at(j).getVec3().at(k).getZ() - littleOffset));
					}
					movedTriangles.push_back(Triangle(vertices));
					vertices.clear();
				}
				otherTetrahedrons.push_back(Tetrahedron(movedTriangles));
				CreateTetrahedrons(recursionLevel - 1, otherTetrahedrons, triangles);
				otherTetrahedrons.clear();
				movedTriangles.clear();


				all_triangles.clear();
			}
		}
		CreateTetrahedrons(recursionLevel - 1, tetrahedrons, triangles);
	}


}
void VertexManager::createTrianglesFromVertexAndMids(int recursionLevel, std::vector<Vertex> *allVertices, Triangle &n_triangle)
{
	if (recursionLevel > 0)
	{
		for (unsigned int i = 0; i < n_triangle.getVec3().size(); i++)
		{
			if (i == 0)
			{
				if (recursionLevel == 1)
				{
					addVertices(allVertices, n_triangle);
				}
				else
				{
					std::vector<Vertex> n_vertices;
					n_vertices.push_back(n_triangle.getVec3().at(0));
					n_vertices.push_back(n_triangle.getMids().at(0));
					n_vertices.push_back(n_triangle.getMids().at(1));
					Triangle tmpTriangle = Triangle(n_vertices);
					createTrianglesFromVertexAndMids(recursionLevel - 1, allVertices, tmpTriangle);
				}
			}
			if (i == 1)
			{
				if (recursionLevel == 1)
				{
					addVertices(allVertices, n_triangle);
				}
				else
				{
					std::vector<Vertex> n_vertices;
					n_vertices.push_back(n_triangle.getMids().at(0));
					n_vertices.push_back(n_triangle.getVec3().at(1));
					n_vertices.push_back(n_triangle.getMids().at(2));
					Triangle tmpTriangle = Triangle(n_vertices);
					createTrianglesFromVertexAndMids(recursionLevel - 1, allVertices, tmpTriangle);
				}
			}
			if (i == 2)
			{
				if (recursionLevel == 1)
				{
					addVertices(allVertices, n_triangle);
				} 
				else
				{
					std::vector<Vertex> n_vertices;
					n_vertices.push_back(n_triangle.getMids().at(1));
					n_vertices.push_back(n_triangle.getVec3().at(2));
					n_vertices.push_back(n_triangle.getMids().at(2));
					Triangle tmpTriangle = Triangle(n_vertices);
					createTrianglesFromVertexAndMids(recursionLevel - 1, allVertices, tmpTriangle);
				}	
			}
			
		}
	}
}
void VertexManager::SummariseVertices(std::vector<Vertex>* allVertices, std::vector<Triangle> &triangles)
{
	for (Triangle element : triangles)
	{
		addVertices(allVertices, element);
	}
}
void VertexManager::addVertices(std::vector<Vertex>* allVertices, Triangle &triangle)
{
	for (Vertex &element : triangle.getVec3())
	{
		allVertices->push_back(element);
	}
}
void VertexManager::createDataAndIndexArrays(std::vector<Vertex> *vertices)
{

	floats->clear();
	indexArray->clear();
	uniqueVertices->clear();
	
	for (Vertex &element : *vertices)
	{
		insertThisValueToTheArray(element);
	}
	int counter = 0;
	for (Vertex &element : *uniqueVertices)
	{
		floats->push_back(element.getX());
		floats->push_back(element.getY());
		floats->push_back(element.getZ());
		if (counter % 3 == 0)
		{
			floats->push_back(0.0f);
			floats->push_back(0.0f);
		}
		if (counter % 3 == 1)
		{
			floats->push_back(1.0f);
			floats->push_back(0.0f);
		}
		if (counter % 3 == 2)
		{
			floats->push_back(0.5f);
			floats->push_back(1.0f);
		}
		counter++;
	}
	
}

void VertexManager::insertThisValueToTheArray(Vertex &vertex)
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
std::vector<Vertex>* VertexManager::getUniqueVertices()
{
	return uniqueVertices;
}