#ifndef ElementBufferObject_H
#define ElementBufferObject_H

#include "BufferObject.h"

namespace GLShader
{
class ElementBufferObject : public BufferObject
{
public:
	virtual void Bind() const;
	virtual void Unbind() const;

	ElementBufferObject(){};
	ElementBufferObject(const GLuint* indices, int size);
	~ElementBufferObject();
};
}
// Element Buffer Object. A Buffer containing the indicies of the verticies.

#endif // !EBO_H
