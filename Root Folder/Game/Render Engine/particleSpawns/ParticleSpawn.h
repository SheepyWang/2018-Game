#pragma once

#include "../toolbox/maths/vec4.h"

//����λ��������
class ParticleSpawn {
public:
	virtual vec4 getBaseSpawnPosition() = 0;
};