#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

using namespace glm;

class Material {
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setMat4(const std::string& name, const mat4& value);
private:
	std::vector<int> textureIDs;
	int shaderID;
};