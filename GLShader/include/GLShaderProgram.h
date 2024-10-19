#ifndef GLSHADER_PROGRAM_H
#define GLSHADER_PROGRAM_H

#include "GLBaseShader.h"

#include <glad/glad.h>

namespace GLShader
{
class GLShaderProgram
{
private:
	GLuint ID;

private:
	void compileErrors() const;

public:

	GLuint GetID() const { return ID; }

	// Activates the Shader Program
	void Activate() const;

	// Deletes the Shader Program
	void Delete() const;

	void AttachShaders(const GLBaseShader& Vertex, const GLBaseShader& Fragment) const;

	GLShaderProgram();
	~GLShaderProgram();

};
}
#endif // !GLSHADER_PROGRAM_H
