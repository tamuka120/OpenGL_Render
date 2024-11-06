#version 330 core

in vec4 mapped_coords;
out vec4 FragColor;

uniform float color_intensity;

void main()
{
	FragColor = vec4(0.f, 0.f, 1f, 1f) * color_intensity;
}
