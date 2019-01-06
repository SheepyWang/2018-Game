#pragma once

#include "../post processing/gaussian blur/gaussianblur.h"
#include "../post processing/invert color/invertcolor.h"
#include "../radial blur/radialblur.h"
#include "../depth of field/depthoffieldeffect.h"
#include "../bloom/bloomEffect.h"


//0为不做后处理
class PostProcessSelection {
private:
	int TEXTURE_WIDTH = 800;
	int TEXTURE_HEIGHT = 600;

	InvertColor * m_InvertColor;
	GaussianBlur * m_GaussianBlur;
	BloomEffect * m_BloomEffect;
	RadialBlur * m_RadialBlur;
	DepthOfFieldEffect * m_DepthOfFieldEffect;

	Fbo * m_fbo;

	int m_choice = 2;

public:
	PostProcessSelection() {
		m_InvertColor = new InvertColor(TEXTURE_WIDTH, TEXTURE_HEIGHT);
		m_GaussianBlur = new GaussianBlur(TEXTURE_WIDTH, TEXTURE_HEIGHT);
		m_BloomEffect = new BloomEffect(TEXTURE_WIDTH, TEXTURE_HEIGHT);
		m_RadialBlur = new RadialBlur(TEXTURE_WIDTH, TEXTURE_HEIGHT);
		m_DepthOfFieldEffect = new DepthOfFieldEffect(TEXTURE_WIDTH, TEXTURE_HEIGHT);

		m_fbo = FboBuilder(TEXTURE_WIDTH, TEXTURE_HEIGHT).setDepthBuffer(TEXTURE).creat();
	}

	~PostProcessSelection() {
		delete m_InvertColor;
		delete m_GaussianBlur;
		delete m_BloomEffect;
		delete m_RadialBlur;
		delete m_DepthOfFieldEffect;
		delete m_fbo;
	}

	void setChoice() {
		if (DisplayManager::isKeyPressed(GLFW_KEY_0)) {
			m_choice = 0;
		}
		else if (DisplayManager::isKeyPressed(GLFW_KEY_1)) {
			m_choice = 1;
		}
		else if (DisplayManager::isKeyPressed(GLFW_KEY_2)) {
			m_choice = 2;
		}
		else if (DisplayManager::isKeyPressed(GLFW_KEY_3)) {
			m_choice = 3;
		}
		else if (DisplayManager::isKeyPressed(GLFW_KEY_4)) {
			m_choice = 4;
		}
		else if (DisplayManager::isKeyPressed(GLFW_KEY_5)) {
			m_choice = 5;
		}
	}

	void bind() {
		if (m_choice != 0) {
			m_fbo->bindFrameBuffer();
		}
	}

	void unbind() {
		if (m_choice != 0) {
			m_fbo->unbindFrameBuffer();
		}
	}

	void render() {
		if (m_choice == 1) {//灰度
			m_InvertColor->carryOutProcessing(m_fbo->getColourTexture(), 0, true);
		}
		else if (m_choice == 2) {//高斯
			m_GaussianBlur->carryOutProcessing(m_fbo->getColourTexture(), 0, true);
		}
		else if (m_choice == 3) {//高光
			m_BloomEffect->carryOutProcessing(m_fbo->getColourTexture(), 0, true);
		}
		else if (m_choice == 4) {//径像模糊
			m_RadialBlur->applyFilter(true, { m_fbo->getColourTexture() });
		}
		else if (m_choice == 5) {//径像模糊
			m_DepthOfFieldEffect->carryOutProcessing(m_fbo->getColourTexture(), m_fbo->getDepthTexture(), true);
		}
	}
};