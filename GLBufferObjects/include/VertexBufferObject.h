#ifndef VertexBufferObject_H
#define VertexBufferObject_H

#include "BufferObject.h"

// Vertex Buffer Object. A buffer containing the vertices.

/**
 * vertex buffer objects (VBO) that can store a large number of vertices in the GPU's memory.
 *  The advantage of using those buffer objects is that we can send large batches of data all
 *  at once to the graphics card, and keep it there if there's enough memory left, without having
 *  to send data one vertex at a time. Sending data to the graphics card from the CPU is
 *  relatively slow, so wherever we can we try to send as much data as possible at once.
 *  Once the data is in the graphics card's memory the vertex shader has almost instant
 *  access to the vertices making it extremely fast.
 */

namespace GLShader
{
	class VertexBufferObject : public BufferObject
	{
	public:

		/// <summary>
		/// Make this VAO the current Vertex Buffer Object in the OpenGL state.
		/// </summary>
		virtual void Bind() const;

		/// <summary>
		/// Set the current Vertex Buffer Object to nothing in the OpenGL state.
		/// </summary>
		virtual void Unbind() const;

		size_t GetSize() const
		{
			return m_size;
		}

		VertexBufferObject() = default;
		VertexBufferObject(const GLfloat* vertices, size_t size);
		~VertexBufferObject();
	private:
		size_t m_size = 0;
	};
}

#endif // ShaderManager_H
