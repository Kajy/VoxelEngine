#include "UEntity.h"

UEntity::UEntity() :
	_camera(nullptr),
	_moving(false),
	_vaoHandle(0),
	_pos(glm::dvec3(0.0, 0.0, 0.0)),
	_velocity(glm::dvec3(0.0, 0.0, 0.0)),
	_speed(glm::dvec3(10.0, 10.0, 10.0)),
	_gravity(glm::dvec3(0.0, -9.81, 0.0)),
	_effectByGravity(true)
{
}

UEntity::UEntity(glm::vec3 const &pos) :
	_camera(nullptr),
	_moving(false),
	_vaoHandle(0),
	_pos(pos),
	_velocity(glm::dvec3(0.0, 0.0, 0.0)),
	_speed(glm::dvec3(5.0, 5.0, 5.0)),
	_gravity(glm::dvec3(0.0, -0.981, 0.0)),
	_effectByGravity(true)
{
}

UEntity::~UEntity() {}


void		UEntity::attachCameraToEntity(UViewer *camera)
{
	_camera = camera;
	_camera->setCameraPos(glm::dvec3(_pos.x, _pos.y + 1.8, _pos.z));
}


glm::dvec3		UEntity::movePlayerPos(double deltaTime)
{
	glm::dvec3 newPos;

	if (_camera != nullptr) {
		newPos = _camera->moveCameraPos(deltaTime, _velocity * _speed);
		_pos += deltaTime * _velocity *_speed;
		_velocity.x = 0.0;
		_velocity.y = 0.0;
		_velocity.z = 0.0;
		_moving = false;
	}
	else {
		_pos += deltaTime * _velocity *_speed;
		newPos = _pos;
		_velocity.x = 0.0;
		_velocity.y = 0.0;
		_velocity.z = 0.0;
		_moving = false;
	}
	return newPos;
}

void		UEntity::resetVelocity()
{
	_velocity.x = 0;
	_velocity.y = 0;
	_velocity.z = 0;
}

void		UEntity::setVelocity(glm::dvec3 const &velocity)
{
	_velocity += velocity;
	_moving = true;
}

glm::dvec3	UEntity::generateVerticesEntity(CubeFactory const &factory)
{
	// glm::dvec3 pos = (_camera.getPosCamera() + (_camera.getVectorDir() * 10.0) +0.5);
	  //glm::dvec3 pos = _camera->getPosCamera();
	  //_verticesPositions.clear();
	  //std::cout << "[REAL POS : " << pos.x << ", " << pos.y << ", " << pos.z << "]  --- ";
	  //factory.genVerticeCube(pos, _verticesPositions, _texturesCoord, _normalesPositions, _verticesColors, 2, true, true, true, true, true, true);
	  //updateVerticesPlayer();

	return (glm::dvec3(0, 0, 0));
}

void	UEntity::updateVerticesEntity() {

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

void    UEntity::drawEntity()
{
	//glBindVertexArray(_vaoHandle);
	//glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(_verticesPositions.size()));
}
