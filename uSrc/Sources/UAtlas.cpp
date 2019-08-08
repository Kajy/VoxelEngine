#include "UAtlas.h"


UAtlas::UAtlas(CubesContainer *container) :
	_width(0),
	_height(0)
{
	glGenTextures(1, &_idAtlas);
	generateAtlas(container);
}

UAtlas::~UAtlas()
{
}

void		UAtlas::generateAtlas(CubesContainer *container) {

	_atlasData = new ILubyte[1024 * container->size()];
	_width = 16;
	int offset = 0;
	for (int i = 0; i < 255; ++i) {
		if (container->at(i)->getTextures().size() > 0) {
			for (auto const &it : container->at(i)->getTextures()) {
				Cube		*cube = container->at(i);
				_height += it.getHeight();
				memcpy(_atlasData + offset, it.getData(), 1024);
				offset += 1024;
				cube->initBuffer(offset / 1024, container->size());
			}
		}
	}
}

void	UAtlas::bindAtlas() {
	glBindTexture(GL_TEXTURE_2D, _idAtlas);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _atlasData);
	glBindTexture(GL_TEXTURE_2D, 0);
}