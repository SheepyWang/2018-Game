#pragma once

#include "../toolbox/maths/maths_func.h"
#include "../toolbox/Color.h"
#include "particleTexture.h"
#include "../particleSpawns/ParticleSpawn.h"


//��������
class ParticleSystem {
private:
	float m_pps;
	float m_averageSpeed;
	float m_gravityComplient;
	float m_averageLifeLength;
	float m_averageScale;

	float m_speedError;
	float m_lifeError;
	float m_scaleError = 0;

	bool m_randomRotation = false;
	vec4 m_direction;
	vec4 m_offset;
	float m_directionDeviation = 0;		//ƫ��
	
	ParticleTexture m_texture;
	ParticleSpawn * m_spawn;
	Color * m_color;
	bool m_additive;
	float m_alpha = 1;
	float m_fadeIn = 0;
	float m_fadeOut = 1;
	bool m_hasXRotation = false;
	float m_xRotSpeed = 0;
	bool m_directonLocalSpace = false;

	bool m_isDirection = false;	//�Ƿ��з���

	mat4 m_tansformation;

public:
	//����������
	ParticleSystem(ParticleTexture texture, ParticleSpawn * spawn,
		float pps, float speed, float gravityComplient, float lifeLength, float scale);
	//ɫ��������
	ParticleSystem(Color color, bool additive, ParticleSpawn * spawn,
		float pps, float speed, float gravityComplient, float lifeLength, float scale);
	~ParticleSystem();

	//�����ٶȷ���
	void setDirection(vec3 direction, float deviation);
	void setDirectionLocalSpace();
	void setFadeValue(float alpha, float fadeIn, float fadeOut);
	void setOffset(vec3 offset);
	void setXRotation(float speed);
	void setRandomizRotaion();

	//error��0��1֮��
	//0����û�д������.
	void setSpeedError(float error);
	//error��0��1֮��
	//0����û�д������.
	void setLifeError(float error);
	//error��0��1֮��
	//0����û�д������.
	void setScaleError(float error);

	void pulseParticles(vec3 center, float scale);
	void pulseParticles(mat4 transform, float scale);
	void generateParticles(vec3 center, float scale);
	void generateParticles(mat4 transform, float scale);

	void pulseParticles(vec3 center, Color * pColor, float scale);
	void pulseParticles(mat4 transform, Color * pColor, float scale);
	void generateParticles(vec3 center, Color * pColor, float scale);
	void generateParticles(mat4 transform, Color * pColor, float scale);

private:
	void emitParticle(mat4 transform, Color * pOverrideColour, float scaleFactor);
	float generateValue(float average, float errorMargin);
	float generateRotation();

};