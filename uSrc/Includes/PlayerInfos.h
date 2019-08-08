#pragma once

#include <glm/vec3.hpp>
#include "UViewer.h"

class PlayerInfos
{
public:
	PlayerInfos(glm::dvec3 const &pos, glm::dvec3 const &lookAt);
	~PlayerInfos();

	void							updateInfos(glm::dvec3 const &playerPos, glm::dvec3 const &lookAt);
	glm::dvec3 const				&getPlayerPos()	const			{ return _playerPos; }
	glm::ivec3 const				&getPlayerPosBlock() const		{ return _playerPosBlock; }
	glm::ivec3 const				&getPlayerSection()	const		{ return _playerSection; }
	glm::ivec3 const				&getPlayerPosInSection() const	{ return _playerPosInSection; }
	glm::ivec3 const				&getPlayerTargetCube() const	{ return _playerTargetCube; }
	UViewer::Intersection const		&getPlayerPickingBlock() const	{ return _playerPickingBlock; }

	void							setPlayerPickingBlock(UViewer::Intersection const &inter) { _playerPickingBlock._cubePos = inter._cubePos; _playerPickingBlock._normale = inter._normale; }

private:
	glm::dvec3					_playerPos;
	glm::ivec3					_playerPosBlock;
	glm::ivec3					_playerSection;
	glm::ivec3					_playerPosInSection;
	glm::ivec3					_playerTargetCube;
	UViewer::Intersection		_playerPickingBlock;
}; 