#pragma once

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Shader.h"
#include "Node.h"

#include <glm/vec3.hpp>


using namespace glm;

class Camera;
class Material;
//TO DO: Implement Texture class
class Texture;


struct RenderSettings{
	vec4 backGroundColor;
};


typedef std::vector<Node> Scene;

class Renderer {


public:

	Renderer();

	void onRender(const Camera& camera, const RenderSettings& settings, Material* material, int frameIndex);

	void init();

	bool LoadTexture(const char* filename, GLuint& texID);

	Material* CreateMaterialFromFile(const char* vertexPath, const char* fragmentPath);
	void DestroyMaterial(Material* material);
	Texture* CreateTextureFromFile(const char* textureFilename);
	void DestroyTexture(Texture* texture);

	void CreateNode();

private:
	GLuint VAO;
	GLuint shaderIndex;
	Shader shader;

	typedef std::unordered_set<Texture*> Textures;
	typedef std::unordered_map<Material*, Shader> Materials;
	std::unordered_set<Texture*> textures;
	std::unordered_map<Material*, Shader> materials;
};