#pragma once

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Shader.h"
#include "Node.h"

#include <glm/vec3.hpp>

using namespace glm;

//forward class declarations
class Camera;
class Material;
class Texture;
class Mesh;

struct RenderSettings{
	RenderSettings() : backGroundColor(0.0f, 0.0f, 0.0f, 0.0f), width(0), height(0) {};
	vec4 backGroundColor;
	int width;
	int height;
};

struct Vertex {
	vec3 pos;
	vec3 color;
	vec2 uv;
	vec3 normal;
};

enum class MeshType {
	CUBE,
	WIREFRAMECUBE,
	PLANE
};

//TO DO: Move scene to diffrent header file
typedef std::unordered_map<int, Node> Scene;

class Renderer {


public:

	Renderer();

	void onRender(const Camera& camera, const RenderSettings& settings, const Scene& scene, int frameIndex);

	void init();

	bool loadTexture(const char* filename, GLuint& texID);

	Material* createMaterialFromFile(const char* vertexPath, const char* fragmentPath);
	void destroyMaterial(Material* material);

	Texture* createTextureFromFile(const char* textureFilename);
	void destroyTexture(Texture* texture);

	Mesh* createMesh(MeshType type);
	void destroyMesh(Mesh* mesh);

private:
	typedef std::unordered_set<Texture*> Textures;
	typedef std::unordered_map<Material*, Shader> Materials;
	typedef std::unordered_set<Mesh*> Meshes;
	Textures textures;
	Materials materials;
	Meshes meshes;
	
	vec3 computeNormal(const vec3& a, const vec3& b, const vec3& c) const;

	typedef std::vector<Vertex> Vertices;
	typedef std::vector<int> Indices;

	void createCube(Vertices& vertices, Indices& indices) const;
	void createWireframeCube(Vertices& vertices, Indices& indices) const;
	void createPlane(Vertices& vertices, Indices& indices) const;


};