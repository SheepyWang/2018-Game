#include "PostProcessMonitor.h"

MonitorShader * PostProcessMonitor::depthShader;
MonitorShader * PostProcessMonitor::normalShader;
VertexArray * PostProcessMonitor::vao;

enum PostProcessMonitor::TexType :int;

float PostProcessMonitor::texCoords[8] = {
	0.0, 1.0,
	0.0, 0.0,
	1.0, 1.0,
	1.0, 0.0
};

//´°¿ÚÓÒÉÏµã
float PostProcessMonitor::screenCoords[8] = {
	0.5, 1.0,
	0.5, 0.5,
	1.0, 1.0,
	1.0, 0.5
};

void PostProcessMonitor::Init() {

	depthShader = new MonitorShader("temp/DepthTexture.vert", "temp/DepthTexture.frag");
	normalShader = new MonitorShader("temp/normalTexture.vert", "temp/normalTexture.frag");
	vao = new VertexArray;

	Buffer * texBuf = new Buffer(texCoords, 8, 2);
	Buffer * screenBuf = new Buffer(screenCoords, 8, 2);

	vao->addBuffer(texBuf, 0);
	vao->addBuffer(screenBuf, 1);

	delete texBuf;
	delete screenBuf;
}

void PostProcessMonitor::render(GLuint TexID, TexType type) {
	if (type == DepthTextureType) {
		depthShader->enable();
	}
	else if (type == NormalTextureType) {
		normalShader->enable();
	}
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexID);
	vao->bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	vao->unbind();
	glEnable(GL_DEPTH_TEST);
	if (type == DepthTextureType) {
		depthShader->disable();
	}
	else if (type == NormalTextureType) {
		normalShader->disable();
	}
}