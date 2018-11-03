#include "Tetrahedron.h"
#include <iostream>

Tetrahedron::Tetrahedron(std::vector<Triangle> triangles)
{
	/*front = triangles.at(0);
	lewy = triangles.at(1);
	prawy = triangles.at(2);
	spodek = triangles.at(3);*/
	t_triangles = triangles;
}

Tetrahedron::~Tetrahedron()
{
	
}

void Tetrahedron::CreateTetrahedrons(int recursionLevel, std::vector<Tetrahedron> n_tetrahedrons, std::vector<Triangle> &triangles)
{
	std::vector<Tetrahedron> tetrahedrons;
	std::vector<Triangle> all_triangles;
	std::vector<Vertex> n_vertices;
	if (recursionLevel > 0)
	{
		
		for(unsigned int i = 0; i < n_tetrahedrons.size(); i++)
		{
			for (Triangle &n_triangle : n_tetrahedrons.at(i).getTriangles())//4 trójk¹ty
			{
				//lewy dolny wierzcho³ek
				n_vertices.push_back(n_triangle.getVec3().at(0));
				n_vertices.push_back(n_triangle.getMids().at(0));
				n_vertices.push_back(n_triangle.getMids().at(1));
				all_triangles.push_back(Triangle(n_vertices));
				n_vertices.clear();

				//prawy dolny wierzcho³ek
				n_vertices.push_back(n_triangle.getVec3().at(1));
				n_vertices.push_back(n_triangle.getMids().at(0));
				n_vertices.push_back(n_triangle.getMids().at(2));

				all_triangles.push_back(Triangle(n_vertices));
				n_vertices.clear();


				//gorny wierzcho³ek
				n_vertices.push_back(n_triangle.getVec3().at(2));
				n_vertices.push_back(n_triangle.getMids().at(1));
				n_vertices.push_back(n_triangle.getMids().at(2));

				all_triangles.push_back(Triangle(n_vertices));
				n_vertices.clear();


			}
			//spodek tetrahedronu górnego
			n_vertices.push_back(all_triangles.at(2).getVec3().at(1));
			n_vertices.push_back(all_triangles.at(2).getVec3().at(2));
			n_vertices.push_back(all_triangles.at(8).getVec3().at(2));
			all_triangles.push_back(Triangle(n_vertices));
			n_vertices.clear();

			//wewnetrzna czesc lewego tetrahedronu
			n_vertices.push_back(all_triangles.at(0).getVec3().at(1));
			n_vertices.push_back(all_triangles.at(0).getVec3().at(2));
			n_vertices.push_back(all_triangles.at(3).getVec3().at(1));
			all_triangles.push_back(Triangle(n_vertices));
			n_vertices.clear();

			//wewnetrzna czesc prawego tetrahedronu
			n_vertices.push_back(all_triangles.at(0).getVec3().at(1));
			n_vertices.push_back(all_triangles.at(6).getVec3().at(1));
			n_vertices.push_back(all_triangles.at(6).getVec3().at(2));
			all_triangles.push_back(Triangle(n_vertices));
			n_vertices.clear();

			//wewnetrzna czesc tylnego tetrahedronu
			n_vertices.push_back(all_triangles.at(7).getVec3().at(0));
			n_vertices.push_back(all_triangles.at(7).getVec3().at(2));
			n_vertices.push_back(all_triangles.at(4).getVec3().at(1));
			all_triangles.push_back(Triangle(n_vertices));
			n_vertices.clear();


			//górny tetrahedron
			std::vector<Triangle> tetrahedronParts;
			for (unsigned int i = 2; i <= 8; i += 3)
			{
				tetrahedronParts.push_back(all_triangles.at(i));
			}
			tetrahedronParts.push_back(all_triangles.at(12));
			tetrahedrons.push_back(Tetrahedron(tetrahedronParts));
			tetrahedronParts.clear();

			//lewy z przodu tetrahedron
			{
				tetrahedronParts.push_back(all_triangles.at(0));
				tetrahedronParts.push_back(all_triangles.at(3));
				tetrahedronParts.push_back(all_triangles.at(13));
				tetrahedronParts.push_back(all_triangles.at(9));
				tetrahedrons.push_back(Tetrahedron(tetrahedronParts));
				tetrahedronParts.clear();
			}

			//prawy z przodu tetrahedron
			{
				tetrahedronParts.push_back(all_triangles.at(1));
				tetrahedronParts.push_back(all_triangles.at(14));
				tetrahedronParts.push_back(all_triangles.at(6));
				tetrahedronParts.push_back(all_triangles.at(10));
				tetrahedrons.push_back(Tetrahedron(tetrahedronParts));
				tetrahedronParts.clear();
			}

			// tetrahedron z ty³u
			{
				tetrahedronParts.push_back(all_triangles.at(15));
				tetrahedronParts.push_back(all_triangles.at(4));
				tetrahedronParts.push_back(all_triangles.at(7));
				tetrahedronParts.push_back(all_triangles.at(11));
				tetrahedrons.push_back(Tetrahedron(tetrahedronParts));
				tetrahedronParts.clear();
			}
			if (recursionLevel == 1)
			{
				
				for (Triangle triangle : n_tetrahedrons.at(i).getTriangles())
				{
					triangles.push_back(triangle);
				}
				
			}
			all_triangles.clear();
		}
		
		CreateTetrahedrons(recursionLevel - 1, tetrahedrons, triangles);
	}
	
	
}

std::vector<Triangle> Tetrahedron::getTriangles()
{
	return t_triangles;
}