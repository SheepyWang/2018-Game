#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include "../toolbox/maths/maths_func.h"
#include "../toolbox/Color.h"
#include "../toolbox/Transformation.h"
#include "../../Source/main/camera.h"
#include "../environment/environment.h"


#include "ParticleTexture.h"



class Particle {
private:
	//���ӻ�������
	vec3 m_position;
	vec3 m_velocity;
	float m_gravityEffect;
	float m_lifeLength;				//�ܵ�ʱ��
	float m_rotation;
	float m_scale;

	//��ʾЧ����͸��------��ʾ------------��ʾ-----͸��
	//ʱ���᣺-----------m_fadeIn-------m_fadeOut------
	float m_fadeIn = 0;				//�ӿ�ʼ͸������ȫ��ʾ��ʱ��(�ٷֱȣ�0~1
	float m_fadeOut = 1;			//����ȫ��ʾ����ʼ͸����ʱ��(�ٷֱȣ�0~1
	float m_normalAlpha = 1;		//��׼͸����
	
	Color m_color;
	bool m_isColor = false;

	bool m_rotate3D = false;
	float m_rotX = 0;
	float m_rotXSpeed = 0;

	float m_elapsedTime =0 ;		//�Ѿ���ȥ��ʱ��

	ParticleTexture m_texture;

	vec2 m_texOffset1;
	vec2 m_texOffset2;
	float m_blend;
	float m_distance;
	bool m_manualStages = false;

	bool m_decays = true;			//˥����
	
	//TODO��û����
	Transformation * m_parent= nullptr;		

	float m_heightOffset = 0;

public:
	Particle() = default;
	//����������
	Particle(ParticleTexture texture, vec3 position, vec3 velocity, float gravityEffect,
		float lifeLength, float rotation, float scale);
	//����������
	Particle(ParticleTexture texture, vec3 position, float scale, float deathAnimationTime);
	//����������
	Particle(ParticleTexture texture, float scale, float deathAnimationTime, Transformation transform,
		float heightOffset);
	//��ɫ������
	Particle(Color colour, bool additive, vec3 position, vec3 velocity, float gravityEffec,
		float lifeLength, float rotation, float scale);

	void setHeighOffset(float offset) {
		m_heightOffset = offset; 
	}

	void set3dRotation(float speed) {
		m_rotate3D = true;
		m_rotX = rand() % 360;
		m_rotXSpeed = speed;
	}

	void setPosition(vec3 pos) {
		m_position = pos;
	}

	void kill() {
		m_decays = true;
	}

	void setFade(float normalAlpha, float fadeIn, float fadeOut) {
		m_normalAlpha = normalAlpha;
		m_fadeIn = fadeIn;
		m_fadeOut = fadeOut;
	}

	void setManualStage(bool manual) {
		m_manualStages = manual;
	}

	void setStage(int index) {
		m_manualStages = true;
		setTextureOffset(m_texOffset1, index);
		setTextureOffset(m_texOffset2, index);
	}

	void setStages(int preIndex, int nextIndex, float blend) {
		m_manualStages = true;
		setTextureOffset(m_texOffset1, preIndex);
		setTextureOffset(m_texOffset2, nextIndex);
		m_blend = blend;
	}

	Color getColour() {
		return m_color;
	}

	float getDistance() {
		return m_distance;
	}

	vec2 getTexOffset1() {
		return m_texOffset1;
	}

	vec2 getTexOffset2() {
		return m_texOffset2;
	}

	float getBlend() {
		return m_blend;
	}

	ParticleTexture getTexture() {
		return m_texture;
	}

	vec3 getPosition() {
		return m_position;
	}

	float getRotation() {
		return m_rotation;
	}

	float getRotX() {
		return m_rotX;
	}

	float getScale() {
		return m_scale;
	}

	bool update(Camera camera);

	//����͸����
	//��������ʱ�����ӵ�͸���Ȳ��ϱ仯
	float getTransparency();

private:
	void moveParticleNaturally();
	void rotate();
	void followParent();
	void updateTextureCoordInfo();
	void setTextureOffset(vec2 & offset, int index);
	//TODO�����������ӵķ���
	
};


#endif // _PARTICLES_H_
