#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include "glm/glm.hpp"
#include "glm/geometric.hpp"

class UViewer
{
public:

	typedef struct Intersection {
		glm::ivec3	_cubePos;
		glm::ivec3	_normale;
	} Intersection;

	UViewer(glm::vec3 pos, glm::vec3 vec);
	~UViewer();

	glm::dvec3	getPosCamera() const { return _posCamera; }
	glm::dvec3	getPosLookAt() const { return _posLookAt; }
	glm::dvec3	getUpVector() const { return _upVector; }
	glm::dvec3	const &getVectorDir() const { return _vecDir; }
	std::vector<Intersection> const &getIntersections() const { return _intersections; }

	glm::dvec3	moveCameraPos(double speed, glm::dvec3 const &direction);
	glm::dvec3	rotateCamera(double ang, double angY, glm::dvec3 const &vec);

	void		setCameraPos(glm::dvec3 const &vec) { _posCamera = vec; }
	void		setPosLookAt(glm::dvec3 const &vec) { _posLookAt = vec; }

	void		raycasting(glm::dvec3 const &origin, glm::dvec3 const &vecDir, unsigned int radius);
	void		callbackRaycasting(int x, int y, int z, glm::ivec3 const &face);

private:
	glm::dvec3	_posCamera;
	glm::dvec3	_posLookAt;
	glm::dvec3	_vecDir;
	glm::dvec3	_upVector;

	std::vector<Intersection>	_intersections;

	double		_phi;
	double		_theta;


};