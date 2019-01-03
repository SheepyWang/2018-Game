#include "GridGenerator.h"

//����һ��Grid�ڵĶ�������indices
vector<vec3u> GridGenerator::generateGridIndexBuffer(int vertexCount, bool even) {
	int testBit = (vertexCount % 2 == 0) && !even ? 1 : 0;
	int triangleCount = (vertexCount - 1) * (vertexCount - 1) * 2;  //ÿ��С����Ҫ��������������
	vector<vec3u> indices(triangleCount);

	int pointer = 0;
	for (int col = 0; col < vertexCount - 1; col++) {
		for (int row = 0; row < vertexCount - 1; row++) {
			int topLeft = (row * vertexCount) + col;
			int topRight = topLeft + 1;
			int bottomLeft = (row + 1) * vertexCount + col;
			int bottomRight = bottomLeft + 1;
			if (row % 2 == 0) {
				pointer = storeQuad1(indices, pointer, topLeft, topRight, bottomLeft, bottomRight, col % 2 == testBit);
			}
			else {
				pointer = storeQuad2(indices, pointer, topLeft, topRight, bottomLeft, bottomRight, col % 2 == testBit);
			}
		}
	}

	return indices;
}

//�������͵������λ���˳��storeQuad1��storeQuad2
int GridGenerator::storeQuad1(vector<vec3u> &indices, int pointer, int topLeft, int topRight, int bottomLeft, int bottomRight, bool mixed) {
	indices[pointer].x = topLeft;
	indices[pointer].y = bottomLeft;
	indices[pointer].z = mixed ? topRight : bottomRight;
	pointer++;

	indices[pointer].x = bottomRight;
	indices[pointer].y = topRight;
	indices[pointer].z = mixed ? bottomLeft : topLeft;
	pointer++;

	return pointer;
}

int GridGenerator::storeQuad2(vector<vec3u> &indices, int pointer, int topLeft, int topRight, int bottomLeft, int bottomRight, bool mixed) {
	indices[pointer].x = topRight;
	indices[pointer].y = topLeft;
	indices[pointer].z = mixed ? bottomRight : bottomLeft;
	pointer++;

	indices[pointer].x = bottomLeft;
	indices[pointer].y = bottomRight;
	indices[pointer].z = mixed ? topLeft : topRight;
	pointer++;

	return pointer;
}
