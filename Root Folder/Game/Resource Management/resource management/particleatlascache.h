#pragma once

#include <map>
#include "../../Render Engine/particles/particleTexture.h"

class ParticleAtlasCache {

public:
	//TODO:��ʼ������loadALL������Ҫ�ȵ��ò�����Ⱦɫ������
	static Texture TRIANGLE;

	static std::map <int, ParticleTexture> particleTexture;

	static ParticleTexture getAtlas(int id);

	static void loadAtlas(int id, const char * path, int rows, bool additive);

	static void loadALL();
	
};