#pragma once

#include <GL\freeglut.h>
#include <iostream>

//#include <GL/glew.h>

#include <glm/vec3.hpp>
using namespace glm;

class Renderer {
private:
	//GLuint VAO;

public:

	Renderer()/*: VAO(0)*/ {

	}

	void onRender(const vec3& color) {
		std::cout << "Rendering" << std::endl;

		glClearColor(color.x, color.y, color.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void init() {

		/*GLfloat vertices[] = {
			//vertex position //vertex color
			0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f,0.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left 
		};
		//indexed drawing - we will be using the indices to point to a vertex in the vertices array
		GLuint indices[] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};


		GLuint VBO, EBO;
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//we have to change the stride to 6 floats, as each vertex now has 6 attribute values
		//the last value (pointer) is still 0, as the position values start from the beginning
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //the data comes from the currently bound GL_ARRAY_BUFFER
		glEnableVertexAttribArray(0);

		//here the pointer is the size of 3 floats, as the color values start after the 3rd value from the beginning
		//in other words we have to skip the first 3 floats of the vertex attributes to get to the color values
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);
		//the elements buffer must be unbound after the vertex array otherwise the vertex array will not have an associated elements buffer array
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
	}

	void drawCube() {

	}
};