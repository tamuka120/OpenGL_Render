#ifndef VAO_H
#define VAO_H
#include <glad/glad.h>
#include "vbo.h"


class VAO {

private:
	GLuint ID;

public:
	// Make this VAO the current Vertex Array Object
	void Bind();

	// Set the current Vertex Array Object to nothing
	void Unbind();
	void LinkVBO(VBO& VBO, GLuint layout);
	VAO();
	~VAO();

};
#endif // !VAO_H
