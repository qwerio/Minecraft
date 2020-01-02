#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

using namespace glm;

class Texture;

class Material {
public:
	void SetBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
	}

	void SetInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
	}

	void SetFloat(const std::string& name, float value) 
	{
		glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
	}

	void SetMat4(const std::string& name, const mat4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void SetVec3(const std::string& name, const vec3& value)
	{
		int location = glGetUniformLocation(shaderID, name.c_str());
		glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, glm::value_ptr(value));
	}

	//TO DO: add function addTextures;
	std::vector<Texture*> textures;
	int shaderID;
};