#pragma once

#include <iostream>
#include <math.h>

#include "Renderer.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"

#include <glm/vec3.hpp>

#include <GL\freeglut.h>


using namespace glm;

/*TO DO: Add storing and loading functionality
		list of the nodes
		their materials
		camera postiont
*/
class Application {

public:
	Application() : frameIndex(0)
	{

	}

	void onInit() 
	{
		renderer.init();
		groundMaterial = renderer.CreateMaterialFromFile("C:/Users/ASUS/source/repos/Minecraft/shaders/vertex.vs", "C:/Users/ASUS/source/repos/Minecraft/shaders/fragment.fs");
		groundTexture = renderer.CreateTextureFromFile("C:/Users/ASUS/Desktop/grassBlock.jpg");
		groundMaterial->textures.push_back(groundTexture);
		cubeMesh = renderer.CreateMesh(MeshType::CUBE);
	}

	void onDraw() {
		frameIndex++;
		// TODO: update scene
		groundMaterial->setVec3("cameraPos", camera.Position);
		renderer.onRender(camera, settings, scene, frameIndex);
	}

	void onKeyDown(int key) {
	
		switch (key) {
		case(GLUT_KEY_UP):
			camera.ProcessKeyboard(Camera_Movement::FORWARD, 0.016f);
			std::cout << "UP" << std::endl;
			break;
		case(GLUT_KEY_DOWN):
			camera.ProcessKeyboard(Camera_Movement::BACKWARD, 0.016f);
			std::cout << "DOWN" << std::endl;
			break;
		case(GLUT_KEY_RIGHT):
			camera.ProcessKeyboard(Camera_Movement::RIGHT, 0.016f);
			std::cout << "RIGHT" << std::endl;
			break;
		case(GLUT_KEY_LEFT):
			camera.ProcessKeyboard(Camera_Movement::LEFT, 0.016f);
			std::cout << "LEFT" << std::endl;
			break;
		case(GLUT_KEY_F1):
			CreateNode();
			break;
		case(GLUT_KEY_F2):
			DestroyNode();
			break;
		}

	}
	void onPassiveMouseMotion(int x, int y) {
		if (firstMouse)
		{
			lastX = x;
			lastY = y;
			firstMouse = false;
		}
		else
		{
			camera.ProcessMouseMovement(x - lastX, lastY - y);
			lastX = x;
			lastY = y;
		}
	}

	void CreateNode()
	{
		uint64_t index;
		vec3 pos;
		if (!getCellIndex(camera, index, pos))
			return;

		Scene::iterator it = scene.find(index);
		if (it != scene.end())
			return;
		
		//Insert Node to the Scene
		Node& node = scene[index];

		node.model = mat4(
			vec4(1.0f, 0.0f, 0.0f, 0.0f),
			vec4(0.0f, 1.0f, 0.0f, 0.0f),
			vec4(0.0f, 0.0f, 1.0f, 0.0f),
			vec4(pos.x, pos.y, pos.z, 1.0f)
		);

		node.material = groundMaterial;
		node.mesh = cubeMesh;
	}

	void DestroyNode() 
	{
		uint64_t index;
		vec3 pos;

		if (!getCellIndex(camera, index, pos))
			return;

		Scene::iterator it = scene.find(index);
		if (it != scene.end())
		{
			scene.erase(it);
		}
		
	}

	bool getCellIndex(const Camera& camera, uint64_t& index, vec3& pos) const
	{
		pos = floor(camera.Position + camera.Front * 5.0f);
		const int halfDimension = (1 << 19);
		if (abs(pos.x) > float(halfDimension) || abs(pos.y) > float(halfDimension) || abs(pos.z) > float(halfDimension))
			return false;

		uint64 x = pos.x + halfDimension;
		uint64 y = pos.y + halfDimension;
		uint64 z = pos.z + halfDimension;

		index = x | (y << 20) | (z << 40);

		return true;
	}


	//TO DO: Later
	//void onMouseWheel() {}

private:
	int height;
	int width;
	int frameIndex;
	int lastX;
	int lastY;
	bool firstMouse = true;
	RenderSettings settings;
	Renderer renderer;
	Camera camera;
	Scene scene;
	Material *groundMaterial;
	Texture *groundTexture;
	Mesh* cubeMesh;
};