#include "VertexBufferObject.h"

namespace GLShader
{
	VertexBufferObject::VertexBufferObject(const GLfloat* vertices, int size)
	{
		SPDLOG_DEBUG("INITALISED VBO {}", ID);
		glGenBuffers(1, &ID);

		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		Unbind();
	}

	VertexBufferObject::~VertexBufferObject()
	{
		Unbind();
		SPDLOG_DEBUG("TERMINATE VBO {}", ID);
		glDeleteBuffers(1, &ID);
	}
}