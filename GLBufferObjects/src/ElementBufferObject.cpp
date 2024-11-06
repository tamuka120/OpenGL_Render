#include "ElementBufferObject.h"

namespace GLShader
{
	void ElementBufferObject::Bind() const
	{
		if (ID == 0xFFFFFFFF)
			return;

		SPDLOG_DEBUG("EBO BIND {}", ID);
		BufferObject::Bind(GL_ELEMENT_ARRAY_BUFFER);
	}

	void ElementBufferObject::Unbind() const
	{
		SPDLOG_DEBUG("EBO UNBIND {}", ID);
		BufferObject::Unbind(GL_ELEMENT_ARRAY_BUFFER);
	}

	ElementBufferObject::ElementBufferObject(const GLuint* indices, int size)
	{
		glGenBuffers(1, &ID);
		SPDLOG_DEBUG("GENERATE EBO {}", ID);

		ElementBufferObject::Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
		ElementBufferObject::Unbind();
	}

	ElementBufferObject::~ElementBufferObject()
	{
		ElementBufferObject::Unbind();
		SPDLOG_DEBUG("TERMINATE EBO {}", ID);
	}
}