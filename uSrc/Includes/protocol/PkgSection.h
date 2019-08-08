#pragma once

#include "glm/vec3.hpp"

class PkgSection
{
public:
	PkgSection(int x, int y, int z) :
		_x(x),
		_y(y),
		_z(z)
	{
		_ids = new short[4096];
		_values = new char[4096];
	};

	~PkgSection() {
	};

	void		setIds(short *ptr) { _ids = ptr; }
	glm::ivec3	getOrigin() const { return glm::ivec3(_x, _y, _z); }
	short		*getIds() const { return _ids; }

private:
	int					_x;
	int					_y;
	int					_z;
	short				*_ids;
	char				*_values;
};