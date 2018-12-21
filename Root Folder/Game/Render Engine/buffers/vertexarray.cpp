#include "vertexarray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_ArrayID);
}

VertexArray::~VertexArray() {
	for (int i = 0; i < m_Buffers.size(); i++)
		delete m_Buffers[i];
	glDeleteVertexArrays(1, &m_ArrayID);
}

void VertexArray::addBuffer(Buffer *buffer, GLuint index) {
	bind();
	buffer->bind();
	
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
	m_Buffers.push_back(buffer);

	buffer->unbind();
	unbind();
}

//���ʵ������ɢ�Ļ���
//���е����ݶ�Ĭ��ΪGLFLOAT
//Ĭ��ʵ���仯��Ϊ 1
//������index��ʾ��ӻ����λ��
//������dataFormat��ʾ�������ڻ�������ĸ�ʽ
void VertexArray::addInterLeavedBuffer(Buffer * buffer, int index, const std::vector<int> & dataFormat) {

	bind();
	buffer->bind();

	int LEN = dataFormat.size();

	//ͳ�����ݲ���
	int total = 0;
	for (int i = 0; i < LEN; i++) {
		total += dataFormat[i];
	}
	int vertexByteCount = sizeof(GL_FLOAT) * total;


	total = 0;
	for (int i = 0; i < LEN; i++) {
		//���ö����ʽ
		glVertexAttribPointer(index + i, dataFormat[i], GL_FLOAT, GL_FALSE, vertexByteCount, (GLvoid *)(total * sizeof(GL_FLOAT)));
		//���ö�������
		glEnableVertexAttribArray(index + i);
		//ʵ�ֶ�ʵ����
		glVertexAttribDivisor(index + i, 1);
		//����ƫ��
		total += dataFormat[i];
	}

	m_Buffers.push_back(buffer);

	buffer->unbind();
	unbind();

}

void VertexArray::bind() const {
	glBindVertexArray(m_ArrayID);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}