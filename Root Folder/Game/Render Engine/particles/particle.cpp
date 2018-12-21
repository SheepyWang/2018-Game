#include "particle.h"
#include "../basics/DIsplayManager.h"


//TODO:��Ҫ�ֶ���ӵ������б���


Particle::Particle(ParticleTexture texture, vec3 position, vec3 velocity,
	float gravityEffect, float lifeLength, float rotation, float scale) {
	m_texture = texture;	
	m_position = position;
	m_velocity = velocity;
	m_gravityEffect = gravityEffect;
	m_lifeLength = lifeLength;
	m_rotation = rotation;
	m_scale = scale;
	//ParticleMaster.addParticle(this);
}

Particle::Particle(ParticleTexture texture, vec3 position, float scale, float deathAnimationTime) {
	m_texture = texture;
	m_position = position;
	m_scale = scale;
	m_lifeLength = deathAnimationTime;
	m_rotation = 0;
	m_gravityEffect = 0;
	//ParticleMaster.addParticle(this);
}

Particle::Particle(ParticleTexture texture, float scale, float deathAnimationTime,
	Transformation transform, float heightOffset) {
	m_texture = texture;
	m_scale = scale;
	m_lifeLength = deathAnimationTime;
	m_heightOffset = heightOffset;
	m_rotation = 0;
	m_gravityEffect = 0;
	//TODO:tansformû��
	//ParticleMaster.addParticle(this);
}

Particle::Particle(Color colour, bool additive, vec3 position, vec3 velocity,
	float gravityEffec, float lifeLength, float rotation, float scale) {
	m_color = colour;
	m_position = position;
	m_velocity = velocity;
	m_gravityEffect = gravityEffec;
	m_lifeLength = lifeLength;
	m_rotation = rotation;
	m_scale = scale;
	m_isColor = true;
	//ParticleMaster.addColourParticle(this, additive);
}


//TODO��û����ƺ�
bool Particle::update(Camera camera) {
	if (m_parent == nullptr) {
		moveParticleNaturally();
	}
	else{
		followParent();
	}
	rotate();
	if (!m_isColor && !m_manualStages) {
		updateTextureCoordInfo();
	}
	vec3 vdistance = m_position - camera.getPosition();
	m_distance =
		vdistance.x * vdistance.x +
		vdistance.y * vdistance.y +
		vdistance.z * vdistance.z;
	if (m_decays) {
		//TODO����ʱ��getDelta���棬�������滻�ɶ�Ӧ��ֵ
		m_elapsedTime += DisplayManager::getDelta();
	}
	//����Ҫ͸���仯������
	//��û����ʾ�귵����
	return !m_decays || m_elapsedTime < m_lifeLength;
}

float Particle::getTransparency() {

	//ʱ�����Űٷֱ�
	float lightFactor = m_elapsedTime / m_lifeLength;

	if (lightFactor < m_fadeIn) {//��û����ȫ��ʾ
		float factor = lightFactor / m_fadeIn;
		return factor * m_normalAlpha;
	}
	else if (lightFactor > m_fadeOut) {//�Ѿ���ȫ��ʾ��ʼ��ʧ͸��
		float factor = 1 - (lightFactor - m_fadeOut) / (1 - m_fadeOut);
		return factor * m_normalAlpha;
	}
	else {//����ʱ����ȫ��ʾ
		return 1;
	}
}

void Particle::moveParticleNaturally(){//��������
	//�ܵ�����Ӱ�� y����ٶȳ���������仯
	m_velocity.y += EnvironmentVariables::GRAVITY * m_gravityEffect * DisplayManager::getDelta();

	//�����ƶ����λ��
	//TODO����ʱ��getDelta���棬�������滻�ɶ�Ӧ��ֵ
	m_position.x += m_velocity.x * DisplayManager::getDelta();
	m_position.y += m_velocity.y * DisplayManager::getDelta();
	m_position.z += m_velocity.z * DisplayManager::getDelta();

}

void Particle::rotate() {
	if (m_rotate3D) {
		m_rotX += DisplayManager::getDelta() * m_rotXSpeed;
	}
}

void Particle::followParent() {
	//TODO:û��ʵ�֣���Ҫtransformation
}


//���ӵ���ͼΪn*n��������ͼ��ÿ��ȡ���е�һ��С�飬����ȡ������
void Particle::updateTextureCoordInfo() {
	float lifeFactor = m_elapsedTime / m_lifeLength; 
	printf(" m_elapsedTime = %f ,m_lifeLength = %f , lifeFactor = %f\n", m_elapsedTime, m_lifeLength, lifeFactor);
	if (lifeFactor >= 1.0f) {
		m_elapsedTime = 0;
	}
	int stageCount = m_texture.getNumberOfRows() * m_texture.getNumberOfRows();//��������
	float atlasProgression = lifeFactor * stageCount;//���ڶ�Ӧ����
	int index1 = floor(atlasProgression);//����ȡ��
	int index2 = index1 < stageCount - 1 ? index1 + 1 : index1;
	m_blend = fmod(atlasProgression, 1);
	setTextureOffset(m_texOffset1, index1);
	setTextureOffset(m_texOffset2, index2);
}

//�������ǰ���Ӷ��ڲ���С������Ͻ�����
void Particle::setTextureOffset(vec2 & offset, int index) {
	int column = index % m_texture.getNumberOfRows();
	int row = index / m_texture.getNumberOfRows();
	offset.x = (float)column / m_texture.getNumberOfRows();
	offset.y = (float)row / m_texture.getNumberOfRows();
}