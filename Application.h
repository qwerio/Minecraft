#pragma once

#include <iostream>
#include <math.h>
#include <stdlib.h>

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

	void onInit(const RenderSettings& settings)
	{	
		this->settings = settings;
		renderer.init();

		std::vector<std::string> texturePaths;
		texturePaths.push_back("C:/Users/ASUS/Desktop/grassBlock.jpg");
		texturePaths.push_back("C:/Users/ASUS/Desktop/diamondOre.png");
		
		for (const std::string& path : texturePaths) 
		{
			Material* material = renderer.createMaterialFromFile("C:/Users/ASUS/source/repos/Minecraft/shaders/vertex.vs", "C:/Users/ASUS/source/repos/Minecraft/shaders/fragment.fs");
			groundMaterials.push_back(material);
			material->textures.push_back(renderer.createTextureFromFile(path.c_str()));
		}

		cubeMesh = renderer.createMesh(MeshType::CUBE);

		Material* wireFrameMaterial = renderer.createMaterialFromFile("C:/Users/ASUS/source/repos/Minecraft/shaders/vertex.vs", "C:/Users/ASUS/source/repos/Minecraft/shaders/wireFrame.fs");
		scene[nextNodeId] = Node(nextNodeId);
		Mesh* cubeWireframeMesh = renderer.createMesh(MeshType::WIREFRAMECUBE);
		wireFrameCube = &scene[nextNodeId];
		wireFrameCube->id = nextNodeId;
		wireFrameCube->material = wireFrameMaterial;
		wireFrameCube->mesh = cubeWireframeMesh;
		nextNodeId++;

		
		Material* materialPreviewMaterial = renderer.createMaterialFromFile("C:/Users/ASUS/source/repos/Minecraft/shaders/screenPlane.vs", "C:/Users/ASUS/source/repos/Minecraft/shaders/screenPlane.fs");
		materialPreviewMaterial->textures.push_back(groundMaterials[currentGroundMaterial]->textures[0]);
		scene[nextNodeId] = Node(nextNodeId);
		Mesh* materialPreviewMesh = renderer.createMesh(MeshType::PLANE);
		materialPreviewNode = &scene[nextNodeId];
		materialPreviewNode->id = nextNodeId;
		materialPreviewNode->material = materialPreviewMaterial;
		materialPreviewNode->mesh = materialPreviewMesh;
		float aspectRatio = float(settings.width) / settings.height;

		mat4 translation = mat4(
			vec4(1.0f, 0.0f, 0.0f, 0.0f),
			vec4(0.0f, 1.0f, 0.0f, 0.0f),
			vec4(0.0f, 0.0f, 1.0f, 0.0f),
			vec4(-1.0f, 0.75f, 0.0f, 1.0f)
		);

		materialPreviewNode->model = translation * mat4(
			vec4(0.25f / aspectRatio, 0.0f, 0.0f, 0.0f),
			vec4(0.0f, 0.25f, 0.0f, 0.0f),
			vec4(0.0f, 0.0f, 1.0f, 0.0f),
			vec4(0.0f, 0.0, 0.0f, 1.0f)
		);

		nextNodeId++;

	}

	void onDraw(float delta)
	{
		frameIndex++;
		// TODO: update scene

		uint64_t cellIndex;
		vec3 pos;

		if (!getCellIndex(camera, cellIndex, pos))
			return;

		wireFrameCube->model = mat4(
			vec4(1.0f, 0.0f, 0.0f, 0.0f),
			vec4(0.0f, 1.0f, 0.0f, 0.0f),
			vec4(0.0f, 0.0f, 1.0f, 0.0f),
			vec4(pos.x, pos.y, pos.z, 1.0f)
		);

		updateDestructionAnimations(delta);
		renderer.onRender(camera, settings, scene, frameIndex);
	}

	void onKeyDown(int key, float delta) 
	{
		switch (key)
		{
		case(GLUT_KEY_UP):
			camera.processKeyboard(Camera_Movement::FORWARD, delta);
			break;
		case(GLUT_KEY_DOWN):
			camera.processKeyboard(Camera_Movement::BACKWARD, delta);
			break;
		case(GLUT_KEY_RIGHT):
			camera.processKeyboard(Camera_Movement::RIGHT, delta);
			break;
		case(GLUT_KEY_LEFT):
			camera.processKeyboard(Camera_Movement::LEFT, delta);
			break;
		case(GLUT_KEY_F1):
			createNode();
			break;
		case(GLUT_KEY_F2):
			destroyNode();
			break;
		case(GLUT_KEY_F7):
			currentGroundMaterial++;
			if (currentGroundMaterial >= groundMaterials.size())
				currentGroundMaterial -= groundMaterials.size();
			materialPreviewNode->material->textures[0] = groundMaterials[currentGroundMaterial]->textures[0];
			break;
		case(GLUT_KEY_F8):
			currentGroundMaterial--;
			if (currentGroundMaterial < 0)
				currentGroundMaterial += groundMaterials.size();
			materialPreviewNode->material->textures[0] = groundMaterials[currentGroundMaterial]->textures[0];
			break;
		}

	}

	void onPassiveMouseMotion(int x, int y) 
	{
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);

		if (firstMouse)
		{
			lastX = x;
			lastY = y;
			firstMouse = false;
		}
		else
		{
			camera.processMouseMovement(float(x - lastX), float(lastY - y));
			lastX = x;
			lastY = y;
		}
		
	}

	void createNode()
	{
		uint64_t cellIndex;
		vec3 pos;

		if (!getCellIndex(camera, cellIndex, pos))
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

	void destroyNode()
	{
		uint64_t cellIndex;
		vec3 pos;

		if (!getCellIndex(camera, cellIndex, pos))
			return;

		SceneLookUp::iterator it = sceneLookUp.find(cellIndex);

		if (it != sceneLookUp.end())
		{
			Scene::iterator nodeIterator = scene.find(it->second);
			startDestructionAnimation(pos, nodeIterator->second.material);
			scene.erase(nodeIterator);
			sceneLookUp.erase(it);

		}
		
	}

	bool getCellIndex(const Camera& camera, uint64_t& index, vec3& pos) const
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

	void startDestructionAnimation(const vec3& pos, Material* material)
	{
		const int subdivisions = 9;
		const int elementsCount = subdivisions * subdivisions * subdivisions;
		const float scale = 1.0f / subdivisions;
		DestructionAnimationNodes nodes;
		nodes.resize(elementsCount);
		for (int z = 0; z < subdivisions; z++)
		{
			for (int y = 0; y < subdivisions; y++)
			{
				for (int x = 0; x < subdivisions; x++)
				{
					scene[nextNodeId] = Node(nextNodeId);
					Node* node = &scene[nextNodeId];
					node->id = nextNodeId;
					node->material = material;
					node->mesh = cubeMesh;
					mat4 translation = mat4(
						vec4(1.0f, 0.0f, 0.0f, 0.0f),
						vec4(0.0f, 1.0f, 0.0f, 0.0f),
						vec4(0.0f, 0.0f, 1.0f, 0.0f),
						vec4(pos.x + scale * x, pos.y + scale * y, pos.z + scale * z, 1.0f)
					);
					node->model = translation * mat4(
						vec4(scale, 0.0f, 0.0f, 0.0f),
						vec4(0.0f, scale, 0.0f, 0.0f),
						vec4(0.0f, 0.0f, scale, 0.0f),
						vec4(0.0f, 0.0f, 0.0f, 1.0f)
					);

					nextNodeId++;


					float u = ((rand() % 100) * 0.02f - 1.0f) * M_PI;
					float v = ((rand() % 100) * 0.01f);
					float r0 = sin(u) * sqrt(1.0f - v * v);
					float r1 = v;
					float r2 = cos(u) * sqrt(1.0f - v * v);
					const int index = (z * subdivisions + y) * subdivisions + x;
					DestructionAnimationNode& animationNode = nodes[index];
					animationNode.node = node;
					animationNode.duration = 2.0f;
					animationNode.direction = vec3(r0, r1 * 10.0f, r2);
				}
			}
		}

		destructionAnimations.push_back(nodes);
	}

	void endDestructionAnimation(int& index)
	{
		for (const DestructionAnimationNode& node : destructionAnimations[index])
		{
			scene.erase(scene.find(node.node->id));
		}
		destructionAnimations.erase(destructionAnimations.begin() + index);
		index--;
	}

	void updateDestructionAnimations(float deltaTime)
	{
		for (int i = 0; i < destructionAnimations.size(); i++)
		{
			DestructionAnimationNodes& nodes = destructionAnimations[i];
			bool finished = false;
			for (DestructionAnimationNode& node : nodes)
			{
				node.update(deltaTime, finished);
			}
			if (finished)
				endDestructionAnimation(i);				
		}
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
	Node* materialPreviewNode;
	Texture* groundTexture;
	Mesh* cubeMesh;
	//sceneLookUp - map between cube postion and index in the scene array
	typedef std::unordered_map<uint64, int> SceneLookUp;
	typedef std::vector<Material*> GroundMaterials;
	SceneLookUp sceneLookUp;
	GroundMaterials groundMaterials;


	struct DestructionAnimationNode {
		DestructionAnimationNode() : node(nullptr), duration(0), currentTime(0), velocity(0), direction(0.0f) {}
		Node* node;
		float duration;
		float currentTime;
		float velocity;
		vec3 direction;
		

		void update(float deltaTime, bool& finished)
		{
			currentTime += deltaTime;
			if (currentTime >= duration)
			{
				finished = true;
				return;
			}
			else
			{
				finished = false;
			}

			const vec3 gravity = vec3(0.0f, -9.8f, 0.0f);
			vec3 offset = (direction + gravity) * deltaTime;
			node->model += mat4(
				vec4(0.0f, 0.0f, 0.0f, 0.0f),
				vec4(0.0f, 0.0f, 0.0f, 0.0f),
				vec4(0.0f, 0.0f, 0.0f, 0.0f),
				vec4(offset.x, offset.y, offset.z, 0.0f)
			);
			direction += gravity * deltaTime;
		}
	};

	typedef std::vector<DestructionAnimationNode> DestructionAnimationNodes;
	typedef std::vector<DestructionAnimationNodes> DestructionAnimations;
	DestructionAnimations destructionAnimations;
};