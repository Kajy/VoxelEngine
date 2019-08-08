#pragma once

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ObjectProperties.h"
#include "Texture.h"

class Cube {
private:
	short								_id;
	std::vector<Texture>				_textures;
	std::vector<int>					_bindTextureFaces;
	std::vector<std::vector<float> *>	_textureBufferData;
	std::vector<float>					_normalsBufferData;

	int									_frontIdx, _rearIdx, _upIdx, _leftIdx, _rightIdx, _downIdx;
public:
	Cube();
	Cube(short);
	~Cube();

	short										getId() const { return _id; }
	std::vector<Texture> const					&getTextures() const { return _textures; }
	std::vector<std::vector<float> *> const		&getTextBuff() const { return _textureBufferData; }
	std::vector<float> const					&getNormBuff() const { return _normalsBufferData; }
	std::vector<int> const						&getBindTexture() const { return _bindTextureFaces;}

	int											getFrontIdx() const { return _frontIdx; }
	int											getRearIdx() const { return _rearIdx; }
	int											getUpIdx() const { return _upIdx; }
	int											getLeftIdx() const { return _leftIdx; }
	int											getRightIdx() const { return _rightIdx; }
	int											getDownIdx() const { return _downIdx; }

	void										setFrontIdx(int val) { _frontIdx = val; }
	void										setRearIdx(int val) { _rearIdx = val; }
	void										setUpIdx(int val) { _upIdx = val; }
	void										setLeftIdx(int val) { _leftIdx = val; }
	void										setRightIdx(int val) { _rightIdx = val; }
	void										setDownIdx(int val) { _downIdx = val; }

	void							initBuffer(GLuint offset, GLuint sizeAtlas);
	unsigned int					addTexture(std::string const &path);

}; 

