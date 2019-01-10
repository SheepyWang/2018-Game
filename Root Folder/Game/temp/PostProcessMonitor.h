#pragma once

#include "../Render Engine/buffers/vertexarray.h"
#include "MonitorShader.h"

class PostProcessMonitor {
private:
	static MonitorShader * depthShader;
	static MonitorShader * normalShader;

	static VertexArray * vao;

	static float texCoords[8];
	static float screenCoords[8];

public:
	static enum TexType :int {
		DepthTextureType,
		NormalTextureType
	};

public:
	static void Init();
	static void render(GLuint TexID, TexType type);
	
};

