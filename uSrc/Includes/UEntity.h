#pragma once

#include <vector>
#include "Texture.h"
#include "CubeFactory.h"
#include "UViewer.h"
#include "AABBBox.h"

class   UEntity {

public:
	UEntity();
	UEntity(glm::vec3 const &pos);
	~UEntity();

public:

	void						updateVerticesEntity();
	glm::dvec3					generateVerticesEntity(CubeFactory const &factory);
	void						drawEntity();

	void                        attachCameraToEntity(UViewer *camera);
	void                        detachCameraOfEntity() { _camera = nullptr; }

	glm::dvec3					movePlayerPos(double deltaTime);

public:

	glm::dvec3					getEntityPosition() { return _pos; }
	glm::dvec3					getEntityVelocity() { return _velocity; }
	glm::dvec3					getEntitySpeed() { return _speed; }
	glm::dvec3					getEntityGravity() { return _gravity; }
	bool						isMoving() const { return _moving; }
	UViewer						*getCamera() { return _camera; }

	void						setMoving(bool moving) { _moving = moving; }
	void						setVelocity(glm::dvec3 const &velocity);
	void						setEffectByGravity(bool gravity) { _effectByGravity = gravity; }

	void						resetVelocity();
	
private:
	UViewer						*_camera;
	bool						_moving;
	bool						_effectByGravity;
	glm::dvec3					_pos;
	glm::dvec3					_velocity;
	glm::dvec3					_speed;
	glm::dvec3					_gravity;

private:
	unsigned int				_vaoHandle, _vboVertices, _vboNormals, _vboColors, _vboTextures;

	std::vector<glm::vec3>		_verticesPositions;
	std::vector<float>			_normalesPositions;
	std::vector<glm::vec3>		_verticesColors;
	std::vector<float>			_texturesCoord;
};
