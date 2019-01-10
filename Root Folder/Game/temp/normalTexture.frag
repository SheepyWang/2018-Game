#version 400

uniform sampler2D depthMap;

in vec2 TexCoords;

float near_plane = 0.1f;
float far_plane = 30.0f;

out vec4 FragColor;


void main(){
	FragColor = texture(depthMap, TexCoords);
}
