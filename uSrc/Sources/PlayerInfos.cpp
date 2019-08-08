#include "PlayerInfos.h"

PlayerInfos::PlayerInfos(glm::dvec3 const &pos, glm::dvec3 const &lookAt)
{
	updateInfos(pos, lookAt);
	_playerPickingBlock._cubePos = glm::ivec3(0, 0, 0);
	_playerPickingBlock._normale = glm::ivec3(0, 0, 0);
}

PlayerInfos::~PlayerInfos()
{

}

void	PlayerInfos::updateInfos(glm::dvec3 const &pos, glm::dvec3 const &lookAt)
{
	_playerPos = pos;
	_playerPosBlock = glm::ivec3(pos);
	_playerSection = glm::ivec3((_playerPosBlock.x >> 4) << 4, (_playerPosBlock.y >> 4) << 4, (_playerPosBlock.z >> 4) << 4);
	_playerPosInSection = glm::ivec3(_playerPosBlock.x & 0xF, _playerPosBlock.y & 0xF, _playerPosBlock.z & 0xF);
	_playerTargetCube = glm::ivec3(_playerPosBlock.x + lookAt.x, _playerPosBlock.y + lookAt.y, _playerPosBlock.z + lookAt.z);
} 