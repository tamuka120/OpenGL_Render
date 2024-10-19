#ifndef GLBASE_SHADER_H
#define GLBASE_SHADER_H

#include <filesystem>
#include <string>

#include <glad/glad.h>

namespace GLShader
{
//template<>
//struct fmt::formatter<my_type> : fmt::formatter<std::string>
//{
//	auto format(my_type my, format_context& ctx) const -> decltype(ctx.out())
//	{
//		return format_to(ctx.out(), "[my_type i={}]", my.i);
//	}
//};


class GLBaseShader
{
private:
	GLuint ID = 0;

protected:
	GLenum ShaderType;
	std::string ShaderTypeString;
	
	void compileErrors() const;

public:
	GLuint GetID() const { return ID; }

public:
	GLBaseShader(const std::filesystem::path path, const GLenum type, const std::string& typeString);
	~GLBaseShader();

};
}
#endif // !GLBASE_SHADER_H
