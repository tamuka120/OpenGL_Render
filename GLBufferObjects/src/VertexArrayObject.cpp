#include "VertexArrayObject.h"

namespace GLShader
{
	void VertexArrayObject::Bind() const
	{
		SPDLOG_DEBUG("VAO BIND {}", ID);
		glBindVertexArray(ID);
	}
	void VertexArrayObject::Unbind() const
	{
		SPDLOG_TRACE("VAO UNBIND {}", ID);
		glBindVertexArray(0);
	}

	void VertexArrayObject::BindAllBuffers() const
	{
		Bind();
		VertexBuffer->Bind();
		ElementBuffer->Bind();
	}

	void VertexArrayObject::LinkBuffers()
	{
		SPDLOG_TRACE("VAO({}) LINK VBO({}), EBO({})", ID, VertexBuffer->ID, ElementBuffer->ID);
		glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(layout);
	}
	
	VertexArrayObject::VertexArrayObject(ElementBufferObject* EBO, VertexBufferObject* VBO):
		ElementBuffer(EBO),
		VertexBuffer(VBO)
	{
		glGenVertexArrays(1, &ID);
		SPDLOG_DEBUG("GENERATE VAO {}", ID);
		Bind();
	}
	
	VertexArrayObject::~VertexArrayObject()
	{
		Unbind();
		SPDLOG_DEBUG("TERMINATE VAO {}", ID);
		glDeleteVertexArrays(1, &ID);
	}
}
