#include "ElementBufferObject.h"

namespace GLShader
{
	ElementBufferObject::ElementBufferObject(const GLuint* const indices, int size)
	{
		glGenBuffers(1, &ID);
		SPDLOG_DEBUG("INITALISED EBO {}", ID);

		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, &indices, GL_STATIC_DRAW);
		Unbind();
	}

	ElementBufferObject::~ElementBufferObject()
	{
		Unbind();
		SPDLOG_DEBUG("TERMINATE EBO {}", ID);
	}
}