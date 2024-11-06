#version 330 core

in vec3 vertex_position;
in vec2 texture_coords;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

void main()
{
	gl_Position = perspective * view * model * vec4(vertex_position, 1.0);
	texCoords = texture_coords;
}
