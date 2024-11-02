#version 330 core

in vec4 colour;
out vec4 FragColor;
uniform float color_intensity;
void main()
{
	FragColor = colour * color_intensity;
}
