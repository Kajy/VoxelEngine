#include "CubesContainer.h"



CubesContainer::CubesContainer()
{
} 


CubesContainer::~CubesContainer()
{
}

void		CubesContainer::dump() {
	for (int i = 0; i < 255; ++i) {
		if (_cubesContainer[i].getTextures().size() > 0)
			std::cout << "MATERIAL [" << _cubesContainer[i].getId() << "]\n";
			for (auto const &it : _cubesContainer[i].getTextures()) 
				std::cout << "Texure Path \"" << it.getPathTexture() << "\"" <<  std::endl;
	}
}

GLuint		CubesContainer::size() {
	GLuint size = 0;

	for (int i = 0; i < _cubesContainer.size(); ++i) {
		if (_cubesContainer[i].getTextures().size() > 0) 
			size += _cubesContainer[i].getTextures().size();
	}
	return size;
}