#include "VertexArrayObject.h"

namespace GLShader
{
	void VertexArrayObject::Bind() const
	{
		SPDLOG_TRACE("BIND {}", ID);
		glBindVertexArray(ID);
	}
	void VertexArrayObject::Unbind() const
	{
		SPDLOG_TRACE("UNBIND {}", ID);
		glBindVertexArray(0);
	}
	
	void VertexArrayObject::LinkBufferObjects(const GLuint layout, const ElementBufferObject& EBO, const VertexBufferObject& VBO) const
	{
		Bind();
		VBO.Bind();
		EBO.Bind();
		SPDLOG_TRACE("VAO({}) LINK VBO({}), EBO({})", ID, VBO.ID, EBO.ID);
		glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(layout);
	}
	
	VertexArrayObject::VertexArrayObject()
	{
		Bind();
		SPDLOG_DEBUG("INITIALISE VAO {}", ID);
		glGenVertexArrays(1, &ID);
		Unbind();
	}
	
	VertexArrayObject::~VertexArrayObject()
	{
		Unbind();
		SPDLOG_DEBUG("TERMINATE VAO {}", ID);
		glDeleteVertexArrays(1, &ID);
	}
}
