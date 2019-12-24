#pragma once

#include <iostream>
#include <vector>

#include "Shader.h"

#include <glm/vec3.hpp>

using namespace glm;

class Camera;

class Renderer {
private:
	GLuint VAO;
	GLuint shaderIndex;
	Shader shader;
	std::vector<GLuint> texturesID;

public:

	Renderer();

	void onRender(const Camera& camera,const vec3& color, int frameIndex);

	void init();

	bool LoadTexture(const char* filename, GLuint& texID);
};