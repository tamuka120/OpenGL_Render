#ifndef VertexArrayObject_H
#define VertexArrayObject_H

#include "BufferObject.h"
#include "ElementBufferObject.h"
#include "VertexBufferObject.h"

/**
  * Vertex Array Object. Acts as a container for OpenGL Buffer Objects.

  * A vertex array object (also known as VAO) can be bound just like a vertex buffer object
  * and any subsequent vertex attribute calls from that point on will be stored inside the VAO.
  * This has the advantage that when configuring vertex attribute pointers you only have to
  * make those calls once and whenever we want to draw the object, we can just bind the
  * corresponding VAO. This makes switching between different vertex data and attribute configurations
  * as easy as binding a different VAO. All the state we just set is stored inside the VAO.

*/

namespace GLShader
{
class VertexArrayObject : public BufferObject {
public:

	/// <summary>
	/// Make this VAO the current Vertex Array Object in the OpenGL state.
	/// </summary>
	virtual void Bind() const;

	/// <summary>
	/// Set the current Vertex Array Object to nothing in the OpenGL state.
	/// </summary>
	virtual void Unbind() const; 

	/// <summary>
	/// Links Buffer objects to this Array Object.
	/// <param name="layout">Layout. More Information required</param>
	/// </summary>
	void LinkBuffers();

	void BindAllBuffers() const;

	void SetLayout(GLuint value) { layout = value; }
	GLuint GetLayout() const { return layout; }

	size_t GetVertexBufferSize() const { return VertexBuffer->GetSize(); }

	VertexArrayObject(ElementBufferObject* EBO, VertexBufferObject* VBO);
	virtual ~VertexArrayObject();

private:
	size_t linkedObjectsTotalSize = 0;
	GLuint layout = 0;
	ElementBufferObject* ElementBuffer;
	VertexBufferObject* VertexBuffer;
};
}

#endif // !VertexArrayObject_H
