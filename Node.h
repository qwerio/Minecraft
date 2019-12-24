#pragma once

#include "Material.h"

#include <glm/glm.hpp>

using namespace glm; 

class Node {
private:
	mat4 model;
	Material* material;
	int geometryID;
};

// std::vector<Node>