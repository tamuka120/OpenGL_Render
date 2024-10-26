#ifndef ElementBufferObject_H
#define ElementBufferObject_H

#include "BufferObject.h"

namespace GLShader
{
class ElementBufferObject : public BufferObject
{
public:
	virtual void Bind() const
	{
		if(ID == 0xFFFFFFFF)
		{
			return;
		}
		BufferObject::Bind(GL_ELEMENT_ARRAY_BUFFER); 
	}

	virtual void Unbind() const { BufferObject::Unbind(GL_ELEMENT_ARRAY_BUFFER); };

	ElementBufferObject(){};
	ElementBufferObject(const GLuint* const indices, int size);
	~ElementBufferObject();
};
}
// Element Buffer Object. A Buffer containing the indicies of the verticies.

#endif // !EBO_H
