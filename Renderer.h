#pragma once

#include <iostream>

#include "Shader.h"

#include <glm/vec3.hpp>

using namespace glm;

class Renderer {
private:
	GLuint VAO;
	GLuint shaderIndex;
	Shader shader;
	GLuint textureID;

public:

	Renderer();

	void onRender(const vec3& color);

	void init();

	bool LoadTexture(const char* filename, GLuint& texID);
};