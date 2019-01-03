#ifndef _POSTPROCESSING_FILTER_H_
#define _POSTPROCESSING_FILTER_H_


#include "../shaders/shader.h"
#include "../buffers/vertexarray.h"
#include "../basics/window.h"
#include "FboBuilder.h"

class PostProcessingFilter {
private:
	static float positions[8];
	static int VERTEX_COUNT;
	VertexArray m_vao;
	Shader * m_shader;
	Fbo * m_fbo;

public:
	PostProcessingFilter(Shader * shader, int width, int heigh, bool alpha);
	PostProcessingFilter(Shader * shader);
	//inputTexture�������������
	//�ж������ֱ��ʹ��{ }�Ž�ȥ�ͺ��� ���õ�������һ��vector
	GLuint applyFilter(bool renderToScreen, std::vector<GLuint> inputTextures);
	GLuint getOutputTexture();
	void blitToScreen();
	void cleanUp();
	virtual void prepareShader(Shader * shader);
	void prepare(bool renderToScreen, std::vector<GLuint> inputTextures);
	void finishRendering(bool renderToScreen);
};

#endif // !_POSTPROCESSING_FILTER_H_
