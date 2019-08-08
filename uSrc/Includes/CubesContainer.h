#pragma once

#include <array>
#include "Cube.h"

class CubesContainer
{
public:
	CubesContainer();
	~CubesContainer();

	void		addCube(unsigned int id) {
					Cube  newCube(id);
					_cubesContainer[newCube.getId()] = newCube; };

	Cube const	&searchCubeById(unsigned int id) const {return (_cubesContainer[id]); };
	void		dump();
	GLuint		size();
	Cube		*at(unsigned int i) { return &(_cubesContainer.at(i)); }
private:
	std::array<Cube, 255>	_cubesContainer;
}; 

