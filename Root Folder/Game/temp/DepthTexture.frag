#version 400

uniform sampler2D depthMap;

in vec2 TexCoords;

float near_plane = 0.1f;
float far_plane = 30.0f;

out vec4 FragColor;

// required when using a perspective projection matrix
float LinearizeDepth(float depth){
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));	
}

void main(){             
    float depthValue = texture(depthMap, TexCoords).r;
    FragColor = vec4(vec3(LinearizeDepth(depthValue) / far_plane), 1.0); // perspective
    FragColor = vec4(vec3(depthValue), 1.0); // orthographic
	//FragColor = texture(depthMap, TexCoords);
}
