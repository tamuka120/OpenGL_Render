#version 330 core

in vec2 texCoords;
out vec4 FragColor;

uniform sampler2D ourTexture;
uniform float color_intensity;

void main()
{
	vec4 tex = texture(ourTexture, texCoords);
	tex.xyz *= vec3(texCoords, 0.5f) * color_intensity;
	FragColor = tex;

}
