#pragma once

#include <glm/glm.hpp>

using namespace glm; 

//forward declarations
class Material;
class Mesh;

class Node {

public:
	Node() : id(-1), model(0.0f), material(nullptr), mesh(nullptr) {}
	Node(int id) : id(id), model(0.0f), material(nullptr), mesh(nullptr) {}

	int id;
	mat4 model;
	Material* material;
	Mesh* mesh;
};