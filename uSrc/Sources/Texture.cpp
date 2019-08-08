#include "Texture.h"

Texture::Texture() :
	_pathTexture("")
{
	ilInit();
	iluInit();
}

Texture::Texture(const char *path) :
	_pathTexture(path)
{
	ilInit();
	iluInit();

	initTexture(path);
} 

Texture::~Texture()
{
}

void		Texture::initTexture(const char *path)
{
	ilGenImages(1, &_textureID);
	ilBindImage(_textureID);

	ilutRenderer(ILUT_OPENGL);

	if ((ilLoadImage(path)) == IL_FALSE)
		std::cout << "Error Load Texture File : " << path << std::endl;

	_width = ilGetInteger(IL_IMAGE_WIDTH);
	_height = ilGetInteger(IL_IMAGE_HEIGHT);
	_depth = ilGetInteger(IL_IMAGE_DEPTH);
	_bpp = ilGetInteger(IL_IMAGE_BPP);

	_imgData = new ILubyte[_height * _width * _bpp];
	memcpy(_imgData, ilGetData(), _height * _width * _bpp);

	ilDeleteImage(_textureID);
}


void		Texture::bindTexture() {
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _imgData);
	glBindTexture(GL_TEXTURE_2D, 0);
}