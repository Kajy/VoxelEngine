#pragma once

//#include "GLFW\glfw3.h"
#include "glm/vec3.hpp"

struct ObjectProperties {
	glm::vec3	Kd;
	glm::vec3	Ld;

	glm::vec3	Ks;
	glm::vec3	Ls;

	glm::vec3	Ka;
	glm::vec3	La;
}; 