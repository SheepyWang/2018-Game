#ifndef _PARTICLES_TEXTURE_H_
#define _PARTICLES_TEXTURE_H_

#include "../textures/texture.h"

class ParticleTexture {
private:
	Texture m_texture;
	int m_numberOfRows;
	bool m_additive;
	bool m_glow = false;	//����

public:
	//TODO:Ĭ�Ϲ��캯����һ������
	ParticleTexture() = default;

	ParticleTexture(Texture & texture, int numberOfRows, bool additive) {
		m_texture = texture;
		m_numberOfRows = numberOfRows;
		m_additive = additive;
	};

	ParticleTexture & setGlowy() {
		m_glow = true;
		return *this;
	}

	//Ϊ���ܹ�����MAP��
	friend bool operator < (const ParticleTexture & right, const ParticleTexture & left) {
		if (right.m_texture.getID() != left.m_texture.getID()) {
			return right.m_texture.getID() < left.m_texture.getID();
		}
		return right.m_numberOfRows < left.m_numberOfRows;
	}

	bool getGlows() const {
		return m_glow;
	}

	int getTextureID() const {
		return m_texture.getID();
	}
	int getNumberOfRows() const {
		return m_numberOfRows;
	}
	bool isAdditive() const {
		return m_additive;
	}
};

#endif // !_PARTICLES_TEXTURE_H_
