#include "shader.h"

#include "../Util/utility.h"
#include "spdlog/spdlog.h"


void ShaderProgram::compileErrors(GLuint shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (shader != ID)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	spdlog::info("INITALISE SHADER PROGRAM");
	auto basePath = std::string("Shaders") + sep();
	auto vertexPath = basePath + std::string(vertexFile);
	auto fragmentPath = basePath + std::string(fragmentFile);

	GLuint vertexShader = CreateShader(vertexPath.c_str(), GL_VERTEX_SHADER);
	GLuint fragmentShader = CreateShader(fragmentPath.c_str(), GL_FRAGMENT_SHADER);

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();

	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
	Delete();
}

void ShaderProgram::Activate()
{
	spdlog::info("ACTIVATE SHADER PROGRAM");

	// Tell OpenGL which Shader Program we want to use
	glUseProgram(ID);
}

void ShaderProgram::Delete()
{
	glDeleteProgram(ID);
}

GLuint ShaderProgram::CreateShader(const char* path, GLenum shaderType)
{
	std::string shaderString = readFile(path);
	const char* shaderCode = shaderString.c_str();
	// Create Shader Object and get its reference
	GLuint shaderID = glCreateShader(shaderType);

	// Attach Source Code to the Shader Object
	glShaderSource(shaderID, 1, &shaderCode, NULL);

	// Compile the Shader into machine code
	glCompileShader(shaderID);

	const char* type;

	switch(shaderType)
	{
	case GL_VERTEX_SHADER:
		type = "VERTEX";
		break;
	case GL_FRAGMENT_SHADER:
		type = "FRAGMENT";
		break;
	default:
		type = "NONE";
	}
	spdlog::info("CREATE " + std::string(type) + " SHADER");
	compileErrors(shaderID, type);


	return shaderID;
}
