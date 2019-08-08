#include "AABBBox.h"

AABBBox::AABBBox(glm::dvec3 const &pos, double size, double height)
{
	_vecMin = glm::dvec3(pos.x - (size / 2), pos.y, pos.z - (size / 2));
	_vecMax = glm::dvec3(pos.x + (size / 2), pos.y + height, pos.z + (size / 2));
	_size = size;
}

AABBBox::~AABBBox()
{
}

glm::dvec3 const &AABBBox::getVecMin() const
{
	return (_vecMin);
}

glm::dvec3 const &AABBBox::getVecMax() const
{
	return (_vecMax);
}

double			AABBBox::getSize() const
{
	return (_size);
}
