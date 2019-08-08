#include "Cube.h"

Cube::Cube()
{
	_id = 0;
	for (unsigned int i = 0; i < 6; ++i)
		_bindTextureFaces.push_back(0);}

Cube::Cube(short id) :
	_id(id)
{
	for (unsigned int i = 0; i < 6; ++i)
		_bindTextureFaces.push_back(0);
	if (id == 105) {
		for (int i = 0; i < 6; ++i)
		_bindTextureFaces[i] = 1;
	}
	_frontIdx = 0;
	_rearIdx = 0;
	_upIdx = 0;
	_downIdx = 0;
	_leftIdx = 0;
	_rightIdx = 0;
}

Cube::~Cube() {}


unsigned int		Cube::addTexture(std::string const &path) {
	Texture	newText(path.c_str());

	_textures.push_back(newText);

	return _textures.size() - 1;
}

void	Cube::initBuffer(GLuint offset, GLuint sizeAtlas) {
	//_textureBufferData.clear();
	_normalsBufferData.clear();


	// ----TEXTURE----

	float min = (offset - 1) / (float)sizeAtlas;
	float max = (offset) / (float)sizeAtlas;

	//std::cout << "Offset : " << offset << " UV : " << min << ", " << max << std::endl;
	float posAtlasXmin = 0;
	float posAtlasYmin = min;
	float posAtlasXmax = 1;
	float posAtlasYmax = max;

	float posAtlasXminTop = 0;
	float posAtlasYminTop = min;
	float posAtlasXmaxTop = 1;
	float posAtlasYmaxTop = max;

	std::vector<float>	*newTextureBuffer = new std::vector<float>;

	newTextureBuffer->push_back(posAtlasXmax);	newTextureBuffer->push_back(posAtlasYmax); // 0.1
	newTextureBuffer->push_back(posAtlasXmin);	newTextureBuffer->push_back(posAtlasYmax); // 1.1
	newTextureBuffer->push_back(posAtlasXmin);	newTextureBuffer->push_back(posAtlasYmin); // 2

	newTextureBuffer->push_back(posAtlasXmin);	newTextureBuffer->push_back(posAtlasYmin); // 2
	newTextureBuffer->push_back(posAtlasXmax);	newTextureBuffer->push_back(posAtlasYmin); // 3
	newTextureBuffer->push_back(posAtlasXmax); newTextureBuffer->push_back(posAtlasYmax); // 0
	_textureBufferData.push_back(newTextureBuffer);


	//FRONT
	/*_textureBufferData.push_back(posAtlasXmax);	_textureBufferData.push_back(posAtlasYmax); // 0.1
	_textureBufferData.push_back(posAtlasXmin);	_textureBufferData.push_back(posAtlasYmax); // 1.1
	_textureBufferData.push_back(posAtlasXmin);	_textureBufferData.push_back(posAtlasYmin); // 2

	_textureBufferData.push_back(posAtlasXmin);	_textureBufferData.push_back(posAtlasYmin); // 2
	_textureBufferData.push_back(posAtlasXmax);	_textureBufferData.push_back(posAtlasYmin); // 3
	_textureBufferData.push_back(posAtlasXmax); _textureBufferData.push_back(posAtlasYmax); // 0

	//RIGHT
	_textureBufferData.push_back(posAtlasXmax);	_textureBufferData.push_back(posAtlasYmax); // 1.2
	_textureBufferData.push_back(posAtlasXmin);	_textureBufferData.push_back(posAtlasYmax);
	_textureBufferData.push_back(posAtlasXmin);	_textureBufferData.push_back(posAtlasYmin);



	_textureBufferData.push_back(posAtlasXmin);	_textureBufferData.push_back(posAtlasYmin);
	_textureBufferData.push_back(posAtlasXmax);	_textureBufferData.push_back(posAtlasYmin);
	_textureBufferData.push_back(posAtlasXmax); _textureBufferData.push_back(posAtlasYmax);



	//REAR
	_textureBufferData.push_back(posAtlasXmin);	_textureBufferData.push_back(posAtlasYmin);
	_textureBufferData.push_back(posAtlasXmax);	_textureBufferData.push_back(posAtlasYmin);
	_textureBufferData.push_back(posAtlasXmax);	_textureBufferData.push_back(posAtlasYmax);

	_textureBufferData.push_back(posAtlasXmax);	_textureBufferData.push_back(posAtlasYmax);
	_textureBufferData.push_back(posAtlasXmin);	_textureBufferData.push_back(posAtlasYmax);
	_textureBufferData.push_back(posAtlasXmin); _textureBufferData.push_back(posAtlasYmin);

	//LEFT
	_textureBufferData.push_back(posAtlasXmax);	_textureBufferData.push_back(posAtlasYmax);
	_textureBufferData.push_back(posAtlasXmin);	_textureBufferData.push_back(posAtlasYmax);
	_textureBufferData.push_back(posAtlasXmin);	_textureBufferData.push_back(posAtlasYmin);

	_textureBufferData.push_back(posAtlasXmin);	_textureBufferData.push_back(posAtlasYmin);
	_textureBufferData.push_back(posAtlasXmax);	_textureBufferData.push_back(posAtlasYmin);
	_textureBufferData.push_back(posAtlasXmax); _textureBufferData.push_back(posAtlasYmax);

	//BOTTOM
	_textureBufferData.push_back(posAtlasXmin);	_textureBufferData.push_back(posAtlasYmin);
	_textureBufferData.push_back(posAtlasXmax);	_textureBufferData.push_back(posAtlasYmin);
	_textureBufferData.push_back(posAtlasXmax);	_textureBufferData.push_back(posAtlasYmax);

	_textureBufferData.push_back(posAtlasXmax);	_textureBufferData.push_back(posAtlasYmax);
	_textureBufferData.push_back(posAtlasXmin);	_textureBufferData.push_back(posAtlasYmax);
	_textureBufferData.push_back(posAtlasXmin); _textureBufferData.push_back(posAtlasYmin);

	//TOP

	_textureBufferData.push_back(posAtlasXminTop);	_textureBufferData.push_back(posAtlasYminTop);
	_textureBufferData.push_back(posAtlasXmaxTop);	_textureBufferData.push_back(posAtlasYminTop);
	_textureBufferData.push_back(posAtlasXmaxTop);	_textureBufferData.push_back(posAtlasYmaxTop);

	_textureBufferData.push_back(posAtlasXmaxTop);	_textureBufferData.push_back(posAtlasYmaxTop);
	_textureBufferData.push_back(posAtlasXminTop);	_textureBufferData.push_back(posAtlasYmaxTop);
	_textureBufferData.push_back(posAtlasXminTop);  _textureBufferData.push_back(posAtlasYminTop);*/

	//FRONT
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(0); _normalsBufferData.push_back(1);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(0); _normalsBufferData.push_back(1);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(0); _normalsBufferData.push_back(1);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(0); _normalsBufferData.push_back(1);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(0); _normalsBufferData.push_back(1);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(0); _normalsBufferData.push_back(1);

	//RIGHT
	_normalsBufferData.push_back(1); _normalsBufferData.push_back(0); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(1); _normalsBufferData.push_back(0); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(1); _normalsBufferData.push_back(0); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(1); _normalsBufferData.push_back(0); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(1); _normalsBufferData.push_back(0); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(1); _normalsBufferData.push_back(0); _normalsBufferData.push_back(0);

	//REAR
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(0); _normalsBufferData.push_back(-1);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(0); _normalsBufferData.push_back(-1);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(0); _normalsBufferData.push_back(-1);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(0); _normalsBufferData.push_back(-1);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(0); _normalsBufferData.push_back(-1);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(0); _normalsBufferData.push_back(-1);

	//LEFT
	_normalsBufferData.push_back(-1); _normalsBufferData.push_back(0); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(-1); _normalsBufferData.push_back(0); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(-1); _normalsBufferData.push_back(0); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(-1); _normalsBufferData.push_back(0); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(-1); _normalsBufferData.push_back(0); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(-1); _normalsBufferData.push_back(0); _normalsBufferData.push_back(0);

	//BOTTOM
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(-1); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(-1); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(-1); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(-1); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(-1); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(-1); _normalsBufferData.push_back(0);

	//TOP
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(1); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(1); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(1); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(1); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(1); _normalsBufferData.push_back(0);
	_normalsBufferData.push_back(0); _normalsBufferData.push_back(1); _normalsBufferData.push_back(0);

}
