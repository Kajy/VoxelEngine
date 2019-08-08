#pragma once

#include "glm/vec3.hpp"

class AABBBox 
{
public:
	AABBBox(glm::dvec3 const &pos, double size, double height);
	~AABBBox();

	glm::dvec3 const	&getVecMin() const;
	glm::dvec3 const	&getVecMax() const;
	double				getSize() const;

private:
	glm::dvec3	_vecMin;
	glm::dvec3	_vecMax;
	double		_size;
}; 