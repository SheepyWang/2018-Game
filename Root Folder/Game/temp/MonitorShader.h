#pragma once


#include "../Render Engine/shaders/shader.h"

class MonitorShader :public Shader {

public:


	MonitorShader(const char* vertexPath, const char* fragmentPath)
		:Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();
	}

	virtual void storeAllUniformLocation() {

	}
};
