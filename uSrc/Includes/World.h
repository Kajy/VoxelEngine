#pragma once

#include <vector>
#include <mutex>
#include <unordered_map>
#include <memory>
#include <queue>
#include <thread>
#include "Loader.h"
#include "ModelView.h"
#include "UEntity.h"
#include "CubeFactory.h"
#include "ULight.h"
#include "USection.h"
#include "Texture.h"
#include "UAtlas.h"
#include "protocol/PkgSection.h"
#include "PlayerInfos.h"
#include "UViewer.h"
#include "protocol.h"

#ifndef UWORLD_HEADER
#define UWORLD_HEADER


struct KeyFuncs {
	size_t operator()(const glm::ivec3 &k) const {
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y) ^ std::hash<int>()(k.z);
	}

	bool operator()(const glm::ivec3 &a, const glm::ivec3 &b) const {
		return a.x == b.x && a.y == b.y && a.z == b.z;
	}
};

typedef std::unordered_map<glm::ivec3, USection *, KeyFuncs, KeyFuncs> chunkContainer;

class World {

public:
	World(char const *path, UViewer *camera);
	~World();

public:
	void		addChunk(PkgSection const &);
	void		drawWorld(glm::mat4 &, glm::mat4 &);
	void		addLightOnWorld(glm::vec4 pos, glm::vec3 color, GLfloat intensity, GLfloat power);
	void		setLightPos(glm::vec3 const &pos) { _lights[0].moveLight(glm::vec4(pos.x, pos.y, pos.z, 1)); }
	void		setWorldInfos();
	glm::dvec4	getLightPos() const { return _lights[0]._pos; };
	void		addEvent(PkgSection i) { _queueEvents.push(i); }
	void		addBreakBlockEvent(glm::ivec4 const &pos) { _queueBreak.push(pos); }
	void		addAddBlockEvent(glm::ivec4 const &pos) { _queueAddBlock.push(pos); }
	void		addEntity(UEntity *new_entity) { _entitiesList.push_back(new_entity); }
	void		unloadChunk(glm::ivec3 origin);
	bool		checkCollision(glm::dvec3 const &);
	bool		checkCollisionAABB(glm::dvec3 const &pos, glm::dvec3 const &direction);
	bool		AABBCollideCube(AABBBox const &entityBox, glm::ivec3 const &pos);
	PlayerInfos	*getPlayerInfos() { return &_playerInfos; }
	UEntity		*getEntity(int idx) { return _entitiesList[idx]; }
	CubeFactory	*getCubeFactory() { return &_cubesFactory; }
	UAtlas		*getAtlas() { return _atlas; }

	void		updateEntities(double deltaTime);


	std::queue<glm::ivec4>			*getQueueBreak() { return &_queueBreakNetwork; }
	std::queue<glm::ivec4>			*getQueueAdd() { return &_queueAddNetwork; }
	std::queue<PkgSection>			*getQueueEvent() { return &_queueEvents; }
	std::queue<CubeUpdatePacket>	*getQueueUpdate() { return &_queueUpdateNetwork; }

	void		changeBlock(glm::ivec3 const &pos, int id);
	void		changeBlock(glm::ivec3 const &pos, int id, std::queue<glm::ivec4> *queue);

public:
	bool	_printMethod;
	int		_valueAddBlock;

private:

	ShaderProgram			*_mainShader;
	CubeFactory				_cubesFactory;
	Model					m_model;

	chunkContainer			_chunkList;
	std::vector<UEntity *>	_entitiesList;
	std::vector<ULight>     _lights;

	std::queue<PkgSection>  _queueEvents;

	std::queue<glm::ivec4>	_queueBreak;
	std::queue<glm::ivec4>	_queueBreakNetwork;

	std::queue<glm::ivec4>	_queueAddBlock;
	std::queue<glm::ivec4>	_queueAddNetwork;

	std::queue<CubeUpdatePacket>	_queueUpdateNetwork;

	PlayerInfos				_playerInfos;
	UAtlas					*_atlas;

	std::string _path;

	void CheckUpdate();
	void setupShader();
	void sendInfosToShader(glm::mat4 const &, glm::mat4 const &);
	void useShader(ShaderProgram *);
};

#endif
