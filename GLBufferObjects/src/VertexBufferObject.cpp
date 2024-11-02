#include "VertexBufferObject.h"

namespace GLShader
{
	void VertexBufferObject::Bind() const
	{
		SPDLOG_DEBUG("VBO BIND {}", ID);
		BufferObject::Bind(GL_ARRAY_BUFFER);
	}

	void VertexBufferObject::Unbind() const
	{
		SPDLOG_DEBUG("VBO UNBIND {}", ID);
		BufferObject::Unbind(GL_ARRAY_BUFFER);
	}


	VertexBufferObject::VertexBufferObject(const GLfloat* vertices, size_t size) :
		m_size(size)
	{
		glGenBuffers(1, &ID);
		SPDLOG_DEBUG("GENERATE VBO {}", ID);

		Bind();
		glBufferData(GL_ARRAY_BUFFER, m_size, vertices, GL_STATIC_DRAW);
		Unbind();
	}

	VertexBufferObject::~VertexBufferObject()
	{
		Unbind();
		SPDLOG_DEBUG("TERMINATE VBO {}", ID);
		glDeleteBuffers(1, &ID);
	}
}