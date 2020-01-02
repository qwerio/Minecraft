#pragma once


class Mesh {

public:
	enum class DrawMode {
		LINES,
		TRIANGLES
	};

	DrawMode drawMode;
	int ID;
	int vertexCount;
};