#include "GLBaseShader.h"

#include "spdlog/spdlog.h"
#include <string>
#include <fstream>

namespace
{
	std::string readFile(std::filesystem::path path)
	{
		std::ifstream in(path, std::ios::binary);
		if (in)
		{
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return contents;
		}
		throw(errno);
	}
}

namespace GLShader 
{
	 void GLBaseShader::compileErrors() const
	 {
	 	GLint hasCompiled;
	 	glGetShaderiv(ID, GL_COMPILE_STATUS, &hasCompiled);
	 	if (hasCompiled == GL_FALSE)
	 	{
			char infoLog[1024];
	 		glGetShaderInfoLog(ID, 1024, NULL, infoLog);
	 		SPDLOG_ERROR("{}_SHADER_COMPILATION_ERROR:\n{}", ShaderTypeString, infoLog);
	 	}
	 }

	GLBaseShader::GLBaseShader(const std::filesystem::path path, const GLenum type, const std::string& typeString) : 
		ShaderType(type), 
		ShaderTypeString(typeString)
	{
		std::filesystem::path basePath("C:\\workspace\\OpenGL_Course_Practical\\resources\\shaders");
		SPDLOG_DEBUG("CREATE {} SHADER: {}", typeString, path.string());
		const std::string& ShaderString = readFile(basePath / path);
		const char* ShaderCode = ShaderString.c_str();

		// Create Shader Object and get its reference
		ID = glCreateShader(ShaderType);

		// Attach Source Code to the Shader Object
		glShaderSource(ID, 1, &ShaderCode, NULL);

		// Compile the Shader into machine code
		glCompileShader(ID);
		compileErrors();
	}
	GLBaseShader::~GLBaseShader()
	{
		SPDLOG_DEBUG("TERMINATE {} Shader: {}", ShaderTypeString, ID);
		glDeleteShader(ID);
	};

}
