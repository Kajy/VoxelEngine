#ifndef UTEXTURE_HPP
#define UTEXTURE_HPP

#include <iostream>
#include <GL/glew.h>
#include <string.h>
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

class Texture
{
public:
	Texture();
	Texture(const char *path);
	~Texture();

	GLuint const		&getTextureID() const { return _textureID; }
	void				initTexture(const char *path);
	void				bindTexture();
	std::string const	&getPathTexture() const { return _pathTexture; }

	GLuint				getWidth() const { return _width; }
	GLuint				getHeight() const { return _height; }
	GLuint				getDepth() const { return _depth; }
	GLuint				getBpp() const { return _bpp; }
	ILubyte				*getData() const { return _imgData; }

private:
	GLuint			_textureID;
	GLuint			_width, _height, _depth,  _bpp;
	ILubyte			*_imgData;
	std::string		_pathTexture;
}; 

#endif