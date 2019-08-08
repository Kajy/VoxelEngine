#pragma once

#include "CubesContainer.h"

class UAtlas
{
public:
	UAtlas(CubesContainer *container);
	~UAtlas();

public:
	void	generateAtlas(CubesContainer *container);
	void	bindAtlas();

	GLuint	getAtlasId() const { return _idAtlas; }

private:
	GLuint	_idAtlas;
	ILubyte	*_atlasData;
	GLuint	_width, _height;
};
