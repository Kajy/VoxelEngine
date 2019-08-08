#pragma once

#include <unordered_map>

#include "Texture.h"
#include "CubeFactory.h"
#include "ULight.h"

class USection {
public:
    USection(glm::ivec3 const &origin, short *ids);

    ~USection();

public:

	void						setCube(glm::ivec3 const &pos, short id) {_cubeContainer[(pos.y << 8) | (pos.x << 4) | pos.z] = id; }
	void						setCube(unsigned int idx, short id) { _cubeContainer[idx] = id; }
	short						getIdCubeAtPos(glm::ivec3 const &pos);
	short						*getCubeContainer() const { return (_cubeContainer); }
    void                        cleanSection();
    void                        generateVerticeSection(CubeFactory const &cubesFactory);
    void                        updateVerticesSection();
    void                        drawSection() const;
    void                        setCubeContainer(short *container) { _cubeContainer = container; }


    glm::ivec3 const &getOrigin() const { return _origin; }

    glm::ivec3 const getPos() const { return (glm::ivec3(_origin.x >> 4, _origin.y >> 4, _origin.z >> 4)); }

    bool checkIsTransparentBlock(int value);


private:
    short *_cubeContainer;
    glm::ivec3 _origin;

private:
    GLuint _vaoHandle, _vboVertices, _vboNormals, _vboColors, _vboTextures;

    std::vector<glm::vec3> _verticesPositions;
    std::vector<GLfloat> _normalesPositions;
    std::vector<glm::vec3> _verticesColors;
    std::vector<GLfloat> _texturesCoord;


private:
    GLuint _vaoDebug, _vboVerticesDebug, _vboColorsDebug, _iboDebug;

    std::vector<glm::vec3> _verticesPositionsDebug;
    std::vector<glm::vec3> _verticesColorsDebug;
    std::vector<unsigned int> _indexDebug;

};

