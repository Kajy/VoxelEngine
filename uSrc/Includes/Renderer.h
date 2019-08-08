#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer();
	~Renderer();

private:
	GLuint _vertexBuffer;
	GLuint _colorBuffer;
	GLuint _normalBuffer;
	GLuint _vertexArray;
	GLuint _visibilityBuffer;
	GLsizei _numberOfVertices;
}; 

