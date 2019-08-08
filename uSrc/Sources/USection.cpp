#include "USection.h"

USection::USection(glm::ivec3 const &origin, short *ids) :
	_origin(origin),
	_vaoHandle(0)
{
	_cubeContainer = new short[4096];
	memcpy(_cubeContainer, ids, sizeof(short) * 4096);
}


USection::~USection()
{
	cleanSection();
	if (_vaoHandle != 0) {
		glDeleteVertexArrays(1, &_vaoHandle);
		glDeleteBuffers(1, &_vboVertices);
		glDeleteBuffers(1, &_vboNormals);
		glDeleteBuffers(1, &_vboColors);
		glDeleteBuffers(1, &_vboTextures);
	}
}

bool	USection::checkIsTransparentBlock(int value)
{
	return (value != 0 && value != 4);
}

short	USection::getIdCubeAtPos(glm::ivec3 const &pos) {

	if (pos.x < 16 && pos.x >= 0 && pos.y < 16 && pos.y >= 0 && pos.z < 16 && pos.z >= 0)
		return _cubeContainer[(pos.y << 8) | (pos.x << 4) | pos.z];
	else
		return 0;
}

void	USection::generateVerticeSection(CubeFactory const &_cubesFactory) {
	bool top, bottom, left, right, rear, front;
	cleanSection();
	for (unsigned int i = 0; i < 4096; i++) {
		top = true, bottom = true, left = true, right = true, rear = true, front = true;
		int NoHightValue = i % 256;
		glm::ivec3 pos(NoHightValue >> 4, i >> 8, NoHightValue % 16);
		if (_cubeContainer[(pos.y << 8) | (pos.x << 4) | pos.z] != 0) {
			if (pos.z > 0 && checkIsTransparentBlock(_cubeContainer[(pos.y << 8) | (pos.x << 4) | (pos.z - 1)]) != 0)
				rear = false;
			if (pos.z < 15 && checkIsTransparentBlock(_cubeContainer[(pos.y << 8) | (pos.x << 4) | (pos.z + 1)]) != 0)
				front = false;
			if (pos.y > 0 && checkIsTransparentBlock(_cubeContainer[((pos.y - 1) << 8) | (pos.x << 4) | pos.z]) != 0)
				bottom = false;
			if (pos.y < 15 && checkIsTransparentBlock(_cubeContainer[((pos.y + 1) << 8) | (pos.x << 4) | pos.z]) != 0)
				top = false;
			if (pos.x > 0 && checkIsTransparentBlock(_cubeContainer[(pos.y << 8) | ((pos.x - 1) << 4) | pos.z]) != 0)
				left = false;
			if (pos.x < 15 && checkIsTransparentBlock(_cubeContainer[(pos.y << 8) | ((pos.x + 1) << 4) | pos.z]) != 0)
				right = false;
			glm::vec3 posFinal(pos.x + _origin.x, pos.y + _origin.y, pos.z + _origin.z);
			_cubesFactory.genVerticeCube(posFinal, _verticesPositions, _texturesCoord,
				_normalesPositions, _verticesColors, _cubeContainer[(pos.y << 8) | (pos.x << 4) | pos.z], top, left, right, bottom, rear, front);
		}
	}
	updateVerticesSection();
}

void	USection::cleanSection() {
	_verticesPositions.clear();
	_normalesPositions.clear();
	_texturesCoord.clear();
}

void	USection::updateVerticesSection() {

	if (_vaoHandle == 0) {
		glGenVertexArrays(1, &_vaoHandle);
		glGenBuffers(1, &_vboVertices);
		glGenBuffers(1, &_vboNormals);
		glGenBuffers(1, &_vboColors);
		glGenBuffers(1, &_vboTextures);
	}
	glBindVertexArray(_vaoHandle);
	glBindBuffer(GL_ARRAY_BUFFER, _vboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * _verticesPositions.size(), _verticesPositions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vboNormals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _normalesPositions.size(), _normalesPositions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vboColors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * _verticesColors.size(), _verticesColors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vboTextures);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _texturesCoord.size(), &_texturesCoord[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0); // close vao
}

void USection::drawSection() const {
	glBindVertexArray(_vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(_verticesPositions.size()));
}
