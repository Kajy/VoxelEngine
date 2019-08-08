#pragma once

#include <glm/vec3.hpp>

class ULight
{
public:
	ULight(glm::vec4 pos, glm::vec3 color, GLfloat intensity, GLfloat power) :
		_pos(pos),
		_color(color),
		_intensity(glm::vec3(intensity, intensity, intensity)),
		_power(power)
	{
	}
	~ULight() {};

public:
	void	moveLight(glm::dvec4 const &new_pos) {
		_pos = new_pos;
	}

public:

	glm::dvec4	_pos;
	glm::vec3	_intensity;
	glm::vec3	_color;
	GLfloat		_power;
	
	 
};