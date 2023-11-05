#include "vbo.h"
#include "spdlog/spdlog.h"

void VBO::Bind()
{
	spdlog::info("VBO BIND");
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	spdlog::info("VBO UNBIND");
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::VBO(GLfloat* vertices)
{
	spdlog::info("INITALISE VBO");
	// Introduce the vertices into the VBO
	glGenBuffers(1, &ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

VBO::~VBO()
{
	spdlog::info("TERMINATE VBO");
	glDeleteBuffers(1, &ID);
}