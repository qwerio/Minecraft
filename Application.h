#pragma once

#include <iostream>
#include <math.h>

#include "Renderer.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"

#include <glm/vec3.hpp>
#include <vector>
#include <unordered_map>

#include <GL\freeglut.h>


using namespace glm;

/*TO DO: Add storing and loading functionality
		list of the nodes
		their materials
		camera postions
*/
class Application {

public:
	Application() : 
		frameIndex(0), 
		lastX(0), 
		lastY(0), 
		nextNodeId(0), 
		firstMouse(true), 
		currentGroundMaterial(0), 
		wireFrameCube(nullptr), 
		groundTexture(nullptr), 
		cubeMesh(nullptr) {}

	void OnInit(const RenderSettings& settings)
	{	
		this->settings = settings;
		renderer.Init();

		std::vector<std::string> texturePaths;
		texturePaths.push_back("C:/Users/ASUS/Desktop/grassBlock.jpg");
		texturePaths.push_back("C:/Users/ASUS/Desktop/diamondOre.png");
		
		for (const std::string& path : texturePaths) 
		{
			Material* material = renderer.CreateMaterialFromFile("C:/Users/ASUS/source/repos/Minecraft/shaders/vertex.vs", "C:/Users/ASUS/source/repos/Minecraft/shaders/fragment.fs");
			groundMaterials.push_back(material);
			material->textures.push_back(renderer.CreateTextureFromFile(path.c_str()));
		}

		cubeMesh = renderer.CreateMesh(MeshType::CUBE);

		Material* wireFrameMaterial = renderer.CreateMaterialFromFile("C:/Users/ASUS/source/repos/Minecraft/shaders/vertex.vs", "C:/Users/ASUS/source/repos/Minecraft/shaders/wireFrame.fs");
		scene[nextNodeId] = Node(nextNodeId);
		Node& node = scene[nextNodeId];
		Mesh* cubeWireframeMesh = renderer.CreateMesh(MeshType::WIREFRAMECUBE);
		wireFrameCube = &node;
		wireFrameCube->id = nextNodeId;
		wireFrameCube->material = wireFrameMaterial;
		wireFrameCube->mesh = cubeWireframeMesh;

		nextNodeId++;

	}

	void OnDraw(float delta)
	{
		frameIndex++;
		// TODO: update scene

		uint64_t cellIndex;
		vec3 pos;

		if (!GetCellIndex(camera, cellIndex, pos))
			return;

		wireFrameCube->model = mat4(
			vec4(1.0f, 0.0f, 0.0f, 0.0f),
			vec4(0.0f, 1.0f, 0.0f, 0.0f),
			vec4(0.0f, 0.0f, 1.0f, 0.0f),
			vec4(pos.x, pos.y, pos.z, 1.0f)
		);

		renderer.OnRender(camera, settings, scene, frameIndex);
	}

	void OnKeyDown(int key, float delta) 
	{
		switch (key)
		{
		case(GLUT_KEY_UP):
			camera.ProcessKeyboard(Camera_Movement::FORWARD, delta);
			break;
		case(GLUT_KEY_DOWN):
			camera.ProcessKeyboard(Camera_Movement::BACKWARD, delta);
			break;
		case(GLUT_KEY_RIGHT):
			camera.ProcessKeyboard(Camera_Movement::RIGHT, delta);
			break;
		case(GLUT_KEY_LEFT):
			camera.ProcessKeyboard(Camera_Movement::LEFT, delta);
			break;
		case(GLUT_KEY_F1):
			CreateNode();
			break;
		case(GLUT_KEY_F2):
			DestroyNode();
			break;
		case(GLUT_KEY_F7):
			currentGroundMaterial++;
			if (currentGroundMaterial >= groundMaterials.size())
				currentGroundMaterial -= groundMaterials.size();
			break;
		case(GLUT_KEY_F8):
			currentGroundMaterial--;
			if (currentGroundMaterial < 0)
				currentGroundMaterial += groundMaterials.size();
			break;
		}

	}

	void OnPassiveMouseMotion(int x, int y) 
	{
		if (firstMouse)
		{
			lastX = x;
			lastY = y;
			firstMouse = false;
		}
		else
		{
			camera.ProcessMouseMovement(float(x - lastX), float(lastY - y));
			lastX = x;
			lastY = y;
		}
	}

	void CreateNode()
	{
		uint64_t cellIndex;
		vec3 pos;

		if (!GetCellIndex(camera, cellIndex, pos))
			return;

		SceneLookUp::iterator it = sceneLookUp.find(cellIndex);
		if (it != sceneLookUp.end())
			return;

		//Inserts New Node to the set and initialize node
		scene[nextNodeId] = Node(nextNodeId);
		Node& node = scene[nextNodeId];
		sceneLookUp[cellIndex] = nextNodeId;

		node.model = mat4(
			vec4(1.0f, 0.0f, 0.0f, 0.0f),
			vec4(0.0f, 1.0f, 0.0f, 0.0f),
			vec4(0.0f, 0.0f, 1.0f, 0.0f),
			vec4(pos.x, pos.y, pos.z, 1.0f)
		);
		node.material = groundMaterials[currentGroundMaterial];
		node.mesh = cubeMesh;

		nextNodeId++;
	}

	void DestroyNode() 
	{
		uint64_t cellIndex;
		vec3 pos;

		if (!GetCellIndex(camera, cellIndex, pos))
			return;

		SceneLookUp::iterator it = sceneLookUp.find(cellIndex);
		if (it != sceneLookUp.end()) 
		{	
			scene.erase(scene.find(it->second));
			sceneLookUp.erase(it);
			
		}
	}

	bool GetCellIndex(const Camera& camera, uint64_t& index, vec3& pos) const
	{
		pos = floor(camera.Position + camera.Front * 5.0f);
		const int halfDimension = (1 << 19);
		if (abs(pos.x) > float(halfDimension) || abs(pos.y) > float(halfDimension) || abs(pos.z) > float(halfDimension))
			return false;

		uint64 x = uint64(pos.x) + halfDimension;
		uint64 y = uint64(pos.y) + halfDimension;
		uint64 z = uint64(pos.z) + halfDimension;

		index = x | (y << 20) | (z << 40);

		return true;
	}

private:
	int frameIndex;
	int lastX;
	int lastY;
	int nextNodeId;
	int currentGroundMaterial;
	bool firstMouse;
	RenderSettings settings;
	Renderer renderer;
	Camera camera;
	Scene scene;
	Node* wireFrameCube;
	Texture* groundTexture;
	Mesh* cubeMesh;
	//sceneLookUp - map between cube postion and index in the scene array
	typedef std::unordered_map<uint64, int> SceneLookUp;
	typedef std::vector<Material*> GroundMaterials;
	SceneLookUp sceneLookUp;
	GroundMaterials groundMaterials;
};