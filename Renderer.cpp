#include <GL/glew.h>
#include <SOIL/SOIL.h>

#include <vector>

#include "Renderer.h"
#include "Camera.h"

#define STB_IMAGE_IMPLEMENTATION //if not defined the function implementations are not included
#include "stb_image.h"

using namespace std;
using namespace glm;

Renderer::Renderer() : VAO(0), shaderIndex(0) {

}

void Renderer::onRender(const Camera& camera, const vec3& color, int frameIndex) {
	glClearColor(color.x, color.y, color.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(VAO);

	float theta = frameIndex * 0.01f;

	mat4 rotationY = mat4(
		vec4(cos(theta),  0.0f, sin(theta), 0.0f),
		vec4(0.0f,		  1.0f, 0.0f,		0.0f),
		vec4(-sin(theta), 0.0f, cos(theta), 0.0f),
		vec4(0.0f,		  0.0f, 0.0f,		1.0f)
	);

	mat4 rotationZ = mat4(
		vec4(cos(theta),  sin(theta), 0.0f, 0.0f),
		vec4(-sin(theta), cos(theta), 0.0f, 0.0f),
		vec4(0.0f,        0.0f,		  1.0f, 0.0f),
		vec4(0.0f,		  0.0f,		  0.0f,	1.0f)
	);

	mat4 rotationX = mat4(
		vec4(1.0f, 0.0f, 0.0f, 0.0f),
		vec4(0.0f, cos(theta), -sin(theta), 0.0f),
		vec4(0.0f, sin(theta), cos(theta), 0.0f),
		vec4(0.0f, 0.0f,0.0f, 1.0f)
	);


	shader.use();
	shader.setInt("Texture1", 0);
	shader.setMat4("model", rotationX);
	shader.setMat4("view", camera.GetViewMatrix());
	//TODO: Get width and height from parameters
	shader.setMat4("proj", camera.GetProjMatrix(640, 480));

	glBindTexture(GL_TEXTURE_2D, texturesID[0]);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Renderer::init() {
	if (glewInit()) {
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	GLfloat vertices[] = {
	//  vertex position      vertex color        tex coords    norm

		//front side
		-0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,  0.6f, 0.0f,   0.0f, 0.0f, 0.0f, //	0
		0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,  0.6f, 1.0f,   0.0f, 0.0f, 0.0f, // 	1
		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,  0.3f, 1.0f,   0.0f, 0.0f, 0.0f, //	2
		-0.5f,  0.5f, 0.5f,  0.0f, 1.0f, 0.0f,  0.3f, 0.0f,   0.0f, 0.0f, 0.0f, // 	3
	   //right side
		0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,  0.6f, 0.0f,   0.0f, 0.0f, 0.0f, //	1
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.6f, 1.0f,   0.0f, 0.0f, 0.0f, //	4
		0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.3f, 1.0f,   0.0f, 0.0f, 0.0f, //	5
		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,  0.3f, 0.0f,   0.0f, 0.0f, 0.0f, //	2
		//back side
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.6f, 0.0f,   0.0f, 0.0f, 0.0f, //	4
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.6f, 1.0f,   0.0f, 0.0f, 0.0f, //	7
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.3f, 1.0f,   0.0f, 0.0f, 0.0f, //	6
		0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.3f, 0.0f,   0.0f, 0.0f, 0.0f, //	5
	   //left side
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.6f, 0.0f,   0.0f, 0.0f, 0.0f, // 7
		-0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,  0.6f, 1.0f,   0.0f, 0.0f, 0.0f, //	0
		-0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,  0.3f, 1.0f,   0.0f, 0.0f, 0.0f, //	3
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.3f, 0.0f,   0.0f, 0.0f, 0.0f, // 6
		//top side
		-0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,   0.0f, 0.0f, 0.0f, // 3
		0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.3f, 0.0f,   0.0f, 0.0f, 0.0f, // 2
		0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   0.3f, 1.0f,   0.0f, 0.0f, 0.0f, // 5
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,   0.0f, 0.0f, 0.0f, //	6
		//bottom side
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   0.0f, 0.0f, 0.0f, //	7
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   0.0f, 0.0f, 0.0f, //	4
		0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.6f, 1.0f,   0.0f, 0.0f, 0.0f, //	1
		-0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,  0.6f, 0.0f,   0.0f, 0.0f, 0.0f  // 0
	};

	//indexed drawing - we will be using the indices to point to a vertex in the vertices array
	const int size = 12 * 3;
	
	GLuint indices[size] = {};

	for (int i = 0; i < size; i+=6) {
		int offset = (i / 6) * 4;
		indices[i]     = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;
		indices[i + 3] = 0 + offset;
		indices[i + 4] = 2 + offset;
		indices[i + 5] = 3 + offset;
	}

	GLuint VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	const int stride = (3 + 3 + 2 + 3) * sizeof(float); // 3 floats for pos, 3 floats for color, 2 floats for tex coords, 3 floats for normal

	//we have to change the stride to 6 floats, as each vertex now has 6 attribute values
	//the last value (pointer) is still 0, as the position values start from the beginning
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0); //the data comes from the currently bound GL_ARRAY_BUFFER
	glEnableVertexAttribArray(0);

	//here the pointer is the size of 3 floats, as the color values start after the 3rd value from the beginning
	//in other words we have to skip the first 3 floats of the vertex attributes to get to the color values
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	//the elements buffer must be unbound after the vertex array otherwise the vertex array will not have an associated elements buffer array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	texturesID.resize(1);
	shader.Load("C:/Users/ASUS/source/repos/Minecraft/shaders/vertex.vs", "C:/Users/ASUS/source/repos/Minecraft/shaders/fragment.fs");
	LoadTexture("C:/Users/ASUS/Desktop/grassBlock.jpg", texturesID[0]);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Camera camera(glm::vec3(0.0f, 2.0f, 3.0f));
}

bool Renderer::LoadTexture(const char* filename, GLuint& texID)
{
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //these are the default values for warping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// read the texture
	GLint width, height, channels;
	stbi_set_flip_vertically_on_load(true); //flip the image vertically while loading
	unsigned char* img_data = stbi_load(filename, &width, &height, &channels, 0); //read the image data

	if (img_data)
	{   //3 channels - rgb, 4 channels - RGBA
		GLenum format;
		switch (channels)
		{
		case 4:
			format = GL_RGBA;
			break;
		default:
			format = GL_RGB;
			break;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, img_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture\n");
	}
	stbi_image_free(img_data);

	return true;
}