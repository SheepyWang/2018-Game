#pragma once

#include "DepthOfFieldShader.h"
#include "..\postProcessing\PostProcessingFilter.h"

class CombineFilter :public PostProcessingFilter {
public:
	CombineFilter() :PostProcessingFilter(
		new DepthOfFieldShader(
			"Render Engine/postProcessing/basicPostProcessing.vert",
			"Render Engine/depthOfField/combine.frag")) {

	}

	virtual void prepareShader(Shader * shader) {
		//TODO:����û����ȡ����ľ���
		float focusDistance = 0;
		((DepthOfFieldShader *)shader)->aimDistance->load(focusDistance);
	}

};

