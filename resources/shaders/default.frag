#version 330 core

in vec2 texCoords;
uniform sampler2D ourTexture;
uniform float color_intensity;

out vec4 FragColor;


void main()
{
	vec4 tex = texture(ourTexture, texCoords);
	tex.xyz *= vec3(texCoords, 0.5f) * color_intensity;
	FragColor = tex;

}
