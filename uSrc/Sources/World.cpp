#include "World.h"
#include <iomanip>

World::World(char const *path, UViewer *camera) :
	_path(path),
	_playerInfos(camera->getPosCamera(), camera->getVectorDir())
{
	_printMethod = true;

	addEntity(new UEntity(glm::dvec3(30.0, 100.0, 0.0)));

	
	setupShader();
	addLightOnWorld(glm::vec4(30.0f, 40.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.0f);
}

World::~World() {}


void	World::setWorldInfos() {
	
	_cubesFactory.addCube(1);
	_cubesFactory.getCubeContainer()->at(1)->addTexture(std::string(_path + "/Ressources/Textures/default.png"));
	_cubesFactory.addCube(2);
	_cubesFactory.getCubeContainer()->at(2)->addTexture(std::string(_path + "/Ressources/Textures/fallback.png"));

	_valueAddBlock = 101;
	_atlas = new UAtlas(_cubesFactory.getCubeContainer());
	_atlas->bindAtlas();

	_cubesFactory.dump();
}

void	World::setupShader() {
	std::string		pathVert = _path + "/Ressources/simple.vert";
	std::string		pathFrag = _path + "/Ressources/simple.frag";

	_mainShader = new ShaderProgram();

	_mainShader->initFromFiles(pathVert, pathFrag);
	_mainShader->addUniform("ModelViewMatrix");
	_mainShader->addUniform("ProjectionMatrix");
	_mainShader->addUniform("NormalMatrix");
	_mainShader->addUniform("Material.Kd");
	_mainShader->addUniform("Material.Ks");
	_mainShader->addUniform("Material.Shiness");
	_mainShader->addUniform("nbLights");
	_mainShader->addUniform("Text1");
	_mainShader->addUniform("isText");
}

void	World::sendInfosToShader(glm::mat4 const &view, glm::mat4 const &projection) {

	glm::mat4 model = m_model.getMatrix();
	glm::mat4 mview = view * model;
	glm::mat4 imvp = glm::inverse(mview);
	glm::mat3 nmat = glm::mat3(glm::transpose(imvp)); // normal matrix
	glm::vec3 Kd(0.4f, 0.4f, 0.4f);
	glm::vec3 Ka(0.1f, 0.1f, 0.1f);
	glm::vec3 Ks(0.9f, 0.9f, 0.9f);
	GLfloat Shiness = 180.0f;

	for (int i = 0; i < _lights.size(); ++i) {
		glUniform4fv(_mainShader->uniform("Lights[" + std::to_string(i) + "].Position"), 1, glm::value_ptr(view * _lights[i]._pos));
		glUniform3fv(_mainShader->uniform("Lights[" + std::to_string(i) + "].Color"), 1, glm::value_ptr(_lights[i]._color));
		glUniform3fv(_mainShader->uniform("Lights[" + std::to_string(i) + "].Intensity"), 1, glm::value_ptr(_lights[i]._intensity));
	}

	glUniform1i(_mainShader->uniform("isText"), _printMethod);
	glUniform1i(_mainShader->uniform("Text1"), 0);
	glUniform3fv(_mainShader->uniform("Material.Kd"), 1, glm::value_ptr(Kd));
	glUniform3fv(_mainShader->uniform("Material.Ks"), 1, glm::value_ptr(Ks));
	glUniform1fv(_mainShader->uniform("Material.Shiness"), 1, &Shiness);
	glUniform1i(_mainShader->uniform("nbLights"), (GLint)_lights.size());
	glUniformMatrix4fv(_mainShader->uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(mview));
	glUniformMatrix4fv(_mainShader->uniform("ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix3fv(_mainShader->uniform("NormalMatrix"), 1, GL_FALSE, glm::value_ptr(nmat));
}

void	World::useShader(ShaderProgram *shader) {
	shader->use();
}

void	World::addChunk(PkgSection const &newSection) {

	USection *addChunk = new USection(newSection.getOrigin(), newSection.getIds());
	_chunkList.insert(std::pair<glm::ivec3, USection *>(newSection.getOrigin(), addChunk));
	addChunk->generateVerticeSection(_cubesFactory);
	//std::cout << "Adding Chunk !! [X = " << newSection.getOrigin().x << "] [Y = " << newSection.getOrigin().y << "] [Z = " << newSection.getOrigin().z << "]" << std::endl;

}

void	World::changeBlock(glm::ivec3 const &pos, int id)
{
	glm::ivec3	posInChunk(pos & 0xF);
	glm::ivec3	InChunk((pos >> 4) << 4);

	if (_chunkList.count(InChunk) > 0) {
		_chunkList[InChunk]->setCube(posInChunk, id);
		_chunkList[InChunk]->generateVerticeSection(_cubesFactory);
	}
}

void	World::changeBlock(glm::ivec3 const &pos, int id, std::queue<glm::ivec4> *queue)
{
	glm::ivec3	posInChunk(pos & 0xF);
	glm::ivec3	InChunk((pos >> 4) << 4);

	if (_chunkList.count(InChunk) > 0) {
		std::cout << "Cube ID cassé : " << _chunkList[InChunk]->getIdCubeAtPos(posInChunk) << std::endl;
		_chunkList[InChunk]->setCube(posInChunk, id);
		_chunkList[InChunk]->generateVerticeSection(_cubesFactory);
		queue->push(glm::ivec4(pos.x, pos.y, pos.z, id));
	}
}

void	World::unloadChunk(glm::ivec3 origin) {
	//delete _chunkList[origin];
	_chunkList.erase(origin);
}

void	World::addLightOnWorld(glm::vec4 pos, glm::vec3 color, GLfloat intensity, GLfloat power) {

	_lights.push_back(ULight(pos, color, intensity, power));
	_mainShader->addUniform("Lights[" + std::to_string(_lights.size() - 1) +
		"].Position");
	_mainShader->addUniform("Lights[" + std::to_string(_lights.size() - 1) +
		"].Color");
	_mainShader->addUniform("Lights[" + std::to_string(_lights.size() - 1) +
		"].Intensity");
}

void	World::updateEntities(double deltaTime)
{
	if (_entitiesList.size() > 0) {
		for (auto &it : _entitiesList) {
			//if (it->isMoving()) {
			glm::dvec3 entityVelocity = it->getEntityVelocity();
			entityVelocity.y += (it->getEntityGravity().y / 2) * it->getEntitySpeed().y;
			it->resetVelocity();
			it->setVelocity(entityVelocity);
			if (deltaTime > 0.1) {
				std::cout << "TOO HIGH DELTA TIME !! -> " << deltaTime << std::endl;
			}
			//std::cout << entityVelocity.x << ", " << entityVelocity.y << ", " << entityVelocity.z << std::endl;
			//usleep(1000);
			glm::dvec3 entityPos = it->getEntityPosition();
			entityVelocity = it->getEntityVelocity();
			glm::dvec3 entitySpeed = it->getEntitySpeed();

			if (checkCollisionAABB(entityPos, glm::dvec3(deltaTime * entityVelocity.x * entitySpeed.x, 0.0, 0.0)))
				entityVelocity.x = 0.0;
			if (checkCollisionAABB(entityPos, glm::dvec3(0.0, deltaTime * entityVelocity.y * entitySpeed.y, 0.0)))
				entityVelocity.y = 0.0;
			if (checkCollisionAABB(entityPos, glm::dvec3(0.0, 0.0, deltaTime * entityVelocity.z * entitySpeed.z)))
				entityVelocity.z = 0.0;
			//std::cout << entityVelocity.x << ", " << entityVelocity.y << ", " << entityVelocity.z << std::endl;
			it->resetVelocity();
			it->setVelocity(entityVelocity);
			it->movePlayerPos(deltaTime);
			//}
		}
		_playerInfos.updateInfos(_entitiesList[0]->getCamera()->getPosCamera(), floor(_entitiesList[0]->getCamera()->getVectorDir() * 2.0) / 2.0);
		glm::dvec3 newPos = _entitiesList[0]->getCamera()->getPosCamera();
		_lights[0].moveLight(glm::dvec4(newPos.x, newPos.y + 20.0, newPos.z, 1.0));
	}
}

bool	World::AABBCollideCube(AABBBox const &entityBox, glm::ivec3 const &pos)
{
	glm::ivec3	posInChunk(pos.x & 0xF, pos.y & 0xF, pos.z & 0xF);
	//std::cout << posInChunk.x << ", " << posInChunk.y << ", " << posInChunk.z << std::endl;
	glm::ivec3	InChunk((pos.x >> 4) << 4, (pos.y >> 4) << 4, (pos.z >> 4) << 4);
	//std::cout << "Inchunk [" << InChunk.x << ", " << InChunk.y << ", " << InChunk.z << "]" << std::endl;
	try {
		if (_chunkList.at(InChunk) != NULL && _chunkList.at(InChunk)->getIdCubeAtPos(posInChunk) != 0) {
			AABBBox		cubeBox(glm::dvec3(pos.x + 0.5, pos.y, pos.z + 0.5), 1, 1);

			glm::dvec3	Entity1VecMin = entityBox.getVecMin();
			glm::dvec3	Entity1VecMax = entityBox.getVecMax();

			glm::dvec3	Entity2VecMin = cubeBox.getVecMin();
			glm::dvec3	Entity2VecMax = cubeBox.getVecMax();

			/*std::cout << "Entity1 Min = [" << Entity1VecMin.x << ", " << Entity1VecMin.y << ", " << Entity1VecMin.z << "] ---  "
				<< "Entity1 Max = [" << Entity1VecMax.x << ", " << Entity1VecMax.y << ", " << Entity1VecMax.z << "]\n"
				<< "Entity2 Min = [" << Entity2VecMin.x << ", " << Entity2VecMin.y << ", " << Entity2VecMin.z << "] --- "
				<< "Entity2 Max = [" << Entity2VecMax.x << ", " << Entity2VecMax.y << ", " << Entity2VecMax.z << "]" << std::endl;*/
			return (Entity1VecMax.x > Entity2VecMin.x &&
				Entity1VecMin.x < Entity2VecMax.x &&
				Entity1VecMax.y > Entity2VecMin.y &&
				Entity1VecMin.y < Entity2VecMax.y &&
				Entity1VecMax.z > Entity2VecMin.z &&
				Entity1VecMin.z < Entity2VecMax.z);
		}
		return false;
	}
	catch (std::exception const &err) {
		//std::cout << "No chunk at this pos !" << std::endl;
		return false;
	}
}

bool	World::checkCollisionAABB(glm::dvec3 const &pos, glm::dvec3 const &direction)
{
	glm::ivec3	roundPos(glm::floor(pos.x), glm::floor(pos.y), glm::floor(pos.z));
	glm::ivec3	posInChunk(roundPos.x & 0xF, roundPos.y & 0xF, roundPos.z & 0xF);
	glm::ivec3	InChunk((roundPos.x >> 4) << 4, (roundPos.y >> 4) << 4, (roundPos.z >> 4) << 4);

	glm::dvec3	newPos = pos + direction;

	double		EntitySize = 0.6;
	double		EntityHeight = 1.2;
	AABBBox		EntityBox(newPos, EntitySize, EntityHeight);

	if (direction.x != 0.0) {
		for (int a = -1; a <= 1; ++a) {
			for (int b = -1; b <= 1; ++b) {
				for (int c = 1; c <= glm::ceil(EntitySize); ++c) {
					if (AABBCollideCube(EntityBox, glm::ivec3(roundPos.x + c, roundPos.y + a, roundPos.z + b)) || AABBCollideCube(EntityBox, glm::ivec3(roundPos.x - c, roundPos.y + a, roundPos.z + b)))
						return true;
				}
			}
		}
		return false;
	}
	else if (direction.y != 0.0) {
		for (int a = -1; a <= 1; ++a) {
			for (int b = -1; b <= 1; ++b) {
				for (int c = 1; c <= glm::ceil(EntityHeight); ++c) {
					if (AABBCollideCube(EntityBox, glm::ivec3(roundPos.x + a, roundPos.y + c, roundPos.z + b)) || AABBCollideCube(EntityBox, glm::ivec3(roundPos.x + a, roundPos.y - 1, roundPos.z + b)))
						return true;
				}
			}
		}
		return false;
	}
	else if (direction.z != 0.0) {
		for (int a = -1; a <= 1; ++a) {
			for (int b = -1; b <= 1; ++b) {
				for (int c = 1; c <= glm::ceil(EntitySize); ++c) {
					if (AABBCollideCube(EntityBox, glm::ivec3(roundPos.x + a, roundPos.y + b, roundPos.z + c)) || AABBCollideCube(EntityBox, glm::ivec3(roundPos.x + a, roundPos.y + b, roundPos.z - c)))
						return true;
				}
			}
		}
		return false;
	}
	else
		return (AABBCollideCube(EntityBox, glm::ivec3(roundPos.x, roundPos.y, roundPos.z)));

}

bool	World::checkCollision(glm::dvec3 const &pos)
{
	glm::ivec3	roundPos(glm::floor(pos.x), glm::floor(pos.y), glm::floor(pos.z));
	glm::ivec3	posInChunk(roundPos.x & 0xF, roundPos.y & 0xF, roundPos.z & 0xF);
	glm::ivec3	InChunk((roundPos.x >> 4) << 4, (roundPos.y >> 4) << 4, (roundPos.z >> 4) << 4);

	try {
		if (_chunkList.at(InChunk) == NULL || _chunkList.at(InChunk)->getIdCubeAtPos(posInChunk) != 0)
			return true;
	}
	catch (std::exception const &err) {
		//std::cout << "No chunk at this pos (chheckCollision) !" << std::endl;
		return true;
	}
	return false;
}

void	World::CheckUpdate() {
	for (int i = 0; i < _queueEvents.size(); i++) {
		addChunk(_queueEvents.front());
		_queueEvents.pop();
	}

	for (int i = 0; i < _queueBreak.size(); i++) {
		changeBlock(_queueBreak.front(), 0, &_queueBreakNetwork);
		_queueBreak.pop();
	}

	for (int i = 0; i < _queueAddBlock.size(); i++) {
		changeBlock(_queueAddBlock.front(), _valueAddBlock, &_queueAddNetwork);
		_queueAddBlock.pop();
	}
	
	int _queueUpdateSize = _queueUpdateNetwork.size();
	for (int i = 0; i < _queueUpdateSize; ++i) {
		CubeUpdatePacket	newUpdate = _queueUpdateNetwork.front();
		changeBlock(newUpdate.pos, newUpdate.id);
		_queueUpdateNetwork.pop();
	}
}

void	World::drawWorld(glm::mat4 &view, glm::mat4 &projection) {

	glUseProgram(_mainShader->getProgramId());
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, _atlas->getAtlasId());
	CheckUpdate();
	sendInfosToShader(view, projection);
	useShader(_mainShader);
	for (const auto &it : _chunkList) {
		if (it.second != NULL) {
			it.second->drawSection();
		}
	}

}
