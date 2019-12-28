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

//add width and height to the struct
struct RenderSettings{
	vec4 backGroundColor;
};

enum class MeshType {
	CUBE
};

typedef std::unordered_map<uint64_t, Node> Scene;

class Renderer {


public:

	Renderer();

	void onRender(const Camera& camera, const RenderSettings& settings, const Scene& scene, int frameIndex);

	void init();

	bool LoadTexture(const char* filename, GLuint& texID);

	Material* CreateMaterialFromFile(const char* vertexPath, const char* fragmentPath);
	void DestroyMaterial(Material* material);

	Texture* CreateTextureFromFile(const char* textureFilename);
	void DestroyTexture(Texture* texture);

	Mesh* CreateMesh(MeshType type);
	void DestroyMesh(Mesh* mesh);

	void CreateNode();
	void DestroyNode();

private:
	typedef std::unordered_set<Texture*> Textures;
	typedef std::unordered_map<Material*, Shader> Materials;
	typedef std::unordered_set<Mesh*> Meshes;
	Textures textures;
	Materials materials;
	Meshes meshes;
};