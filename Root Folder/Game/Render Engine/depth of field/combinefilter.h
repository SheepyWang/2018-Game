#pragma once

#include "depthoffieldshader.h"
#include "..\post processing\postprocessingfilter.h"
#include "..\..\Source\main\camera.h"

class CombineFilter :public PostProcessingFilter {
public:
	CombineFilter() :PostProcessingFilter(
		new DepthOfFieldShader(
			"Render Engine/post processing/basicpostprocessing.vert",
			"Render Engine/depth of field/combine.frag")) {

	}

	virtual void prepareShader(Shader * shader) {
		//TODO:����û����ȡ����ľ���
		float focusDistance = Camera::getCamera().getAimDistance();
		((DepthOfFieldShader *)shader)->m_AimDistance->load(focusDistance);
	}

};

