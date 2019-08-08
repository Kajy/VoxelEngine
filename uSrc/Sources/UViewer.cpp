#include "UViewer.h"

UViewer::UViewer(glm::vec3 pos, glm::vec3 vec) :
	_posCamera(pos),
	_vecDir(vec),
	_phi(0.0),
	_theta(0.0)
{
	_vecDir = glm::normalize(_vecDir);
	_posLookAt = glm::vec3(_posCamera.x + _vecDir.x, _posCamera.y + _vecDir.y, _posCamera.z + _vecDir.z);
	_upVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

UViewer::~UViewer()
{
}


glm::dvec3		UViewer::moveCameraPos(double speed, glm::dvec3 const &direction) {
	_posCamera += speed * direction;

	_posLookAt = _posCamera + _vecDir;

	return (_posCamera);
}

glm::dvec3		UViewer::rotateCamera(double theta, double phi, glm::dvec3 const &k)
{
	_phi += phi;
	_theta += theta;

	_phi = glm::max(_phi, -89.9);
	_phi = glm::min(_phi, 89.9);
	float phiRadian = glm::radians(_phi);
	float thetaRadian = glm::radians(_theta);

	double cos_phi = glm::cos(phiRadian);
	double sin_phi = glm::sin(phiRadian);

	double cos_theta = glm::cos(thetaRadian);
	double sin_theta = glm::sin(thetaRadian);

	_vecDir.x = cos_phi * sin_theta;
	_vecDir.y = sin_phi;
	_vecDir.z = cos_phi * cos_theta;


	_posLookAt = _posCamera + _vecDir;

	glm::ivec3 roundPos(_posCamera);
	glm::dvec3 test((roundPos.x & 0xF) + (_posCamera.x - glm::trunc(_posCamera.x)), (roundPos.y & 0xF) + (_posCamera.y - glm::trunc(_posCamera.y)), (roundPos.z & 0xF) + (_posCamera.z - glm::trunc(_posCamera.z)));
	//std::cout << _posCamera.x << ", " << _posCamera.y << ", " << _posCamera.z << " ---> " << test.x << ", " << test.y << ", " << test.z << std::endl;
	raycasting(test, _vecDir, 5);

	return (_vecDir);
}

int mod(int value, int modulus) {
	return (value % modulus + modulus) % modulus;
}

double intbound(double s, double ds) {
	// Find the smallest positive t such that s+t*ds is an integer.
	if (ds < 0) {
		return intbound(-s, -ds);
	}
	else {
		s = mod(s, 1);
		// problem is now s+t*ds = 1
		return (1 - s) / ds;
	}
}

double signum(double x) {
	return x > 0 ? 1 : x < 0 ? -1 : 0;
}



void		UViewer::callbackRaycasting(int x, int y, int z, glm::ivec3 const &face)
{
	Intersection newInter;
	newInter._cubePos = glm::ivec3(x, y, z);
	newInter._normale = face;

	_intersections.push_back(newInter);
}
void		 UViewer::raycasting(glm::dvec3 const &origin, glm::dvec3 const &direction, unsigned int radius) {

	_intersections.clear();

	// Cube containing origin point.
	int x = glm::floor(origin[0]);
	int y = glm::floor(origin[1]);
	int z = glm::floor(origin[2]);

	int originX = x;
	int originY = y;
	int originZ = z;
	// Break out direction vector.
	double dx = direction[0];
	double dy = direction[1];
	double dz = direction[2];
	// Direction to increment x,y,z when stepping.
	double stepX = signum(dx);
	double stepY = signum(dy);
	double stepZ = signum(dz);
	// See description above. The initial values depend on the fractional
	// part of the origin.
	double tMaxX = intbound(origin[0], dx);
	double tMaxY = intbound(origin[1], dy);
	double tMaxZ = intbound(origin[2], dz);
	// The change in t when taking a step (always positive).
	double tDeltaX = stepX / dx;
	double tDeltaY = stepY / dy;
	double tDeltaZ = stepZ / dz;
	// Buffer for reporting faces to the callback.
	glm::dvec3 face;

	// Avoids an infinite loop.
	if (dx == 0 && dy == 0 && dz == 0)
		std::cout << "Error Raycasting vecDir" << std::endl;


	// Rescale from units of 1 cube-edge to units of 'direction' so we can
	// compare with 't'.
	radius /= glm::sqrt(dx*dx + dy * dy + dz * dz);

	while (/* ray has not gone past bounds of world */
		(stepX > 0 ? x < 320000 : x >= 0) &&
		(stepY > 0 ? y < 320000 : y >= 0) &&
		(stepZ > 0 ? z < 320000 : z >= 0)) {

		// Invoke the callback, unless we are not *yet* within the bounds of the
		// world.
		if (!(x < 0 || y < 0 || z < 0 || x >= 320000 || y >= 320000 || z >= 320000))
			//if (x != originX || y != originY || z != originZ)
			callbackRaycasting(x, y, z, face);

		// tMaxX stores the t-value at which we cross a cube boundary along the
		// X axis, and similarly for Y and Z. Therefore, choosing the least tMax
		// chooses the closest cube boundary. Only the first case of the four
		// has been commented in detail.
		if (tMaxX < tMaxY) {
			if (tMaxX < tMaxZ) {
				if (tMaxX > radius) break;
				// Update which cube we are now in.
				x += stepX;
				// Adjust tMaxX to the next X-oriented boundary crossing.
				tMaxX += tDeltaX;
				// Record the normal vector of the cube face we entered.
				face[0] = -stepX;
				face[1] = 0;
				face[2] = 0;
			}
			else {
				if (tMaxZ > radius) break;
				z += stepZ;
				tMaxZ += tDeltaZ;
				face[0] = 0;
				face[1] = 0;
				face[2] = -stepZ;
			}
		}
		else {
			if (tMaxY < tMaxZ) {
				if (tMaxY > radius) break;
				y += stepY;
				tMaxY += tDeltaY;
				face[0] = 0;
				face[1] = -stepY;
				face[2] = 0;
			}
			else {
				// Identical to the second case, repeated for simplicity in
				// the conditionals.
				if (tMaxZ > radius) break;
				z += stepZ;
				tMaxZ += tDeltaZ;
				face[0] = 0;
				face[1] = 0;
				face[2] = -stepZ;
			}
		}
	}
}
