#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>

class ShaderProgram 
{

private:
	// Reference ID of the Shader Program
	GLuint ID;
	GLuint CreateShader(const char* path, GLenum shaderType);
	void compileErrors(GLuint shader, const char* type);

public:

	// Constructor that build the Shader Program from 2 different shaders
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	~ShaderProgram();

	// Activates the Shader Program
	void Activate();

	// Deletes the Shader Program
	void Delete();

};
#endif
