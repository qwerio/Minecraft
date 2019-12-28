#pragma once

#include <iostream>
#include <vector>

#include "Shader.h"
#include "Node.h"

#include <glm/vec3.hpp>

using namespace glm;

class Camera;

struct RenderSettings{
	vec4 backGroundColor;
};

typedef std::vector<Node> Scene;

class Renderer {
private:
	GLuint VAO;
	GLuint shaderIndex;
	Shader shader;
	std::vector<GLuint> texturesID;

public:

	Renderer();

	void onRender(const Camera& camera, const RenderSettings& color, int frameIndex);

	void init();

	bool LoadTexture(const char* filename, GLuint& texID);
};