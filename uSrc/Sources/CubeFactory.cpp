#include "CubeFactory.h"



CubeFactory::CubeFactory()
{
	_colorsContainer.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	_colorsContainer.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	_colorsContainer.push_back(glm::vec3(0.68235f, 0.5372f, 0.255f));
	_colorsContainer.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
}


CubeFactory::~CubeFactory()
{
}


void	CubeFactory::genVerticeCube(glm::vec3 const &pos,
	std::vector<glm::vec3> &vertices,
	std::vector<float> &textures,
	std::vector<float> &normals,
	std::vector<glm::vec3> &color,
	unsigned int cubeId,
	bool top, bool left, bool right, bool bottom, bool rear, bool front) const
{
	std::vector<glm::vec3> vertex;
	vertex.push_back(glm::vec3(pos.x, pos.y, 1 + pos.z));
	vertex.push_back(glm::vec3(1 + pos.x, pos.y, 1 + pos.z));
	vertex.push_back(glm::vec3(1 + pos.x, 1 + pos.y, 1 + pos.z));
	vertex.push_back(glm::vec3(pos.x, 1 + pos.y, 1 + pos.z));
	vertex.push_back(glm::vec3(pos.x, pos.y, pos.z));
	vertex.push_back(glm::vec3(1 + pos.x, pos.y, pos.z));
	vertex.push_back(glm::vec3(1 + pos.x, 1 + pos.y, pos.z));
	vertex.push_back(glm::vec3(pos.x, 1 + pos.y, pos.z));
	std::vector<std::vector<float> *> 	textureBufferData = _cubeContainer.searchCubeById(cubeId).getTextBuff();
	std::vector<float> 					normalBufferData = _cubeContainer.searchCubeById(cubeId).getNormBuff();
	
	if (textureBufferData.size() == 0) {
		textureBufferData = _cubeContainer.searchCubeById(2).getTextBuff();
		normalBufferData = _cubeContainer.searchCubeById(2).getNormBuff();
		cubeId = 2;
	}

	if (front) {
		int idx = _cubeContainer.searchCubeById(cubeId).getFrontIdx();
		textures.insert(textures.end(), &(textureBufferData.at(idx)->at(0)), &(textureBufferData.at(idx)->at(11)) + 1); normals.insert(normals.end(), &normalBufferData[0], &normalBufferData[18]);
		vertices.push_back(vertex[0]);	vertices.push_back(vertex[1]);	vertices.push_back(vertex[2]);
		vertices.push_back(vertex[2]);	vertices.push_back(vertex[3]);	vertices.push_back(vertex[0]);
		color.push_back(_colorsContainer[cubeId]);  color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]);
		color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]);
	}
	if (right) {
		int idx = _cubeContainer.searchCubeById(cubeId).getRightIdx();
		textures.insert(textures.end(), &(textureBufferData.at(idx)->at(0)), &(textureBufferData.at(idx)->at(11)) + 1); normals.insert(normals.end(), &normalBufferData[18], &normalBufferData[36]);
		vertices.push_back(vertex[1]);	vertices.push_back(vertex[5]);	vertices.push_back(vertex[6]);
		vertices.push_back(vertex[6]);	vertices.push_back(vertex[2]);	vertices.push_back(vertex[1]);
		color.push_back(_colorsContainer[cubeId]);  color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]);
		color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]);
	}
	if (rear) {
		int idx = _cubeContainer.searchCubeById(cubeId).getRearIdx();
		textures.insert(textures.end(), &(textureBufferData.at(idx)->at(0)), &(textureBufferData.at(idx)->at(11)) + 1); normals.insert(normals.end(), &normalBufferData[36], &normalBufferData[54]);
		vertices.push_back(vertex[5]);	vertices.push_back(vertex[4]);	vertices.push_back(vertex[7]);
		vertices.push_back(vertex[7]);	vertices.push_back(vertex[6]);	vertices.push_back(vertex[5]);
		
		color.push_back(_colorsContainer[cubeId]);  color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]);
		color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]);
	}
	if (left) {
		int idx = _cubeContainer.searchCubeById(cubeId).getLeftIdx();
		textures.insert(textures.end(), &(textureBufferData.at(idx)->at(0)), &(textureBufferData.at(idx)->at(11)) + 1); normals.insert(normals.end(), &normalBufferData[54], &normalBufferData[72]);
		vertices.push_back(vertex[4]);	vertices.push_back(vertex[0]);	vertices.push_back(vertex[3]);
		vertices.push_back(vertex[3]);	vertices.push_back(vertex[7]);	vertices.push_back(vertex[4]);
		color.push_back(_colorsContainer[cubeId]);  color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]);
		color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]);
	}
	if (bottom) {
		int idx = _cubeContainer.searchCubeById(cubeId).getDownIdx();
		textures.insert(textures.end(), &(textureBufferData.at(idx)->at(0)), &(textureBufferData.at(idx)->at(11)) + 1); normals.insert(normals.end(), &normalBufferData[72], &normalBufferData[90]);
		vertices.push_back(vertex[4]);	vertices.push_back(vertex[5]);	vertices.push_back(vertex[1]);
		vertices.push_back(vertex[1]);	vertices.push_back(vertex[0]);	vertices.push_back(vertex[4]);
		color.push_back(_colorsContainer[cubeId]);  color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]);
		color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]);
	}
	if (top) {
		int idx = _cubeContainer.searchCubeById(cubeId).getUpIdx();
		textures.insert(textures.end(), &(textureBufferData.at(idx)->at(0)), &(textureBufferData.at(idx)->at(11)) + 1); normals.insert(normals.end(), &normalBufferData[90], &normalBufferData[108]);
		vertices.push_back(vertex[3]);	vertices.push_back(vertex[2]);	vertices.push_back(vertex[6]);
		vertices.push_back(vertex[6]);	vertices.push_back(vertex[7]);	vertices.push_back(vertex[3]);
		color.push_back(_colorsContainer[cubeId]);  color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]);
		color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]); color.push_back(_colorsContainer[cubeId]);
	}
}
