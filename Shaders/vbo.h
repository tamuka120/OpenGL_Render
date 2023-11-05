#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

class VBO
{
private:
	GLuint ID;

public:
	// Make this VBO the current Vertex Buffer Object
	void Bind();

	// Set the current Vertex Buffer Object to nothing
	void Unbind();
	VBO(GLfloat* vertices);
	~VBO();
};

#endif // !VBO_H



