#pragma once

#include "CubesContainer.h"

class CubeFactory
{
public:
	CubeFactory();
	~CubeFactory();

public:

	void			genVerticeCube(glm::vec3 const &pos,
							std::vector<glm::vec3> &vertices, std::vector<float> &textures, std::vector<float> &normals, std::vector<glm::vec3> &colors, unsigned int cubeId,
							bool top, bool left, bool right, bool bottom, bool rear, bool front) const;
	void			addCube(unsigned int id) { _cubeContainer.addCube(id); }
	void			dump() { _cubeContainer.dump(); }

	CubesContainer	*getCubeContainer() { return &_cubeContainer; }

private:
	CubesContainer			_cubeContainer;
	std::vector<glm::vec3>	_colorsContainer;
}; 

