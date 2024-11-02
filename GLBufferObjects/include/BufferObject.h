//#ifndef SPDLOG_ACTIVE_LEVEL
//#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
//#endif // SPDLOG_ACTIVE_LEVEL


#ifndef BufferObject_H
#define BufferObject_H


#include <glad/glad.h>

#include "spdlog/spdlog.h"

/**
  * Vertex Array Object. Acts as a container for OpenGL Buffer Objects.

*/

namespace GLShader
{
class BufferObject
{

public:
	GLuint ID{ 0xFFFFFFFF };

public:


	/// <summary>
	/// Make this VAO the current Vertex Array Object in the OpenGL state.
	/// </summary>
	virtual void Bind(GLint bufferType) const
	{
		//SPDLOG_DEBUG("BIND {}", ID);
		glBindBuffer(bufferType, ID);
	}

	/// <summary>
	/// Set the current Vertex Array Object to nothing in the OpenGL state.
	/// </summary>
	virtual void Unbind(GLint bufferType) const
	{
		//SPDLOG_DEBUG("UNBIND {}", ID);
		glBindBuffer(bufferType, 0);
	}

public:
	BufferObject() = default;
	virtual ~BufferObject() = default;
};
}

#endif // !BufferObject_H
