#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include <Triangle.h>
class Tetrahedron
{
private:
	/*Triangle front;
	Triangle lewy;
	Triangle prawy;
	Triangle spodek;*/
	std::vector<Triangle> t_triangles;
public:
	Tetrahedron::Tetrahedron(std::vector<Triangle> triangles);
	Tetrahedron::~Tetrahedron();
	void  Tetrahedron::CreateTetrahedrons(int, std::vector<Tetrahedron>, std::vector<Triangle> &);
	std::vector<Triangle> Tetrahedron::getTriangles();
};
#endif