#pragma once

#include <glm/glm.hpp>

using namespace glm; 

//forward declarations
class Material;
class Mesh;

class Node {
public:
	mat4 model;
	Material* material;
	Mesh* mesh;
};