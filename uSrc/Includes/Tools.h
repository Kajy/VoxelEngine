#pragma once
#include <glm/vec3.hpp>
#include <string>
#include <cstdlib>

class Tools {
public:
	static glm::vec3 colorFromHex(std::string str) {
		int offset = 0;
		if (str[0] == '#')
			offset++;
		std::string r = str.substr(offset, 2);
		offset += 2;
		std::string g = str.substr(offset, 2);
		offset += 2;
		std::string b = str.substr(offset, 2);
		offset += 2;
		return colorFromRGB((float)(std::strtol(r.c_str(), NULL, 16)), (float)(std::strtol(g.c_str(), NULL, 16)), (float)(std::strtol(b.c_str(), NULL, 16)));
	}
	static glm::vec3 colorFromRGB(float R, float G, float B) {
		return glm::vec3(R / 255, G / 255, B / 255);
	}
}; 