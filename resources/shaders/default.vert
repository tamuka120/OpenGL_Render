#version 330 core

// in vec3 vertex_position;
layout (location = 0) in vec3 vertex_position;

uniform float color_intensity;
out vec4 colour;

void main()
{
	colour = vec4(vertex_position.x  + color_intensity, vertex_position.y + color_intensity, vertex_position.z, 1);
	gl_Position = vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1);
	// colour = vec4(1, 0, 0, 1);
	// gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1);
}
