#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexture;
layout(location = 3) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 Color;
out vec2 TexCoord;
out vec3 Pos;
out vec3 Normal;

void main()
{
	gl_Position = proj * view * model * vec4(aPos, 1.0);
	//gl_Position = view * model * vec4(aPos, 1.0);	

	Color = aColor;
	TexCoord = aTexture;
	Pos = (model * vec4(aPos, 1.0)).xyz;
	Normal = (model * vec4(aNormal, 0.0)).xyz;
}