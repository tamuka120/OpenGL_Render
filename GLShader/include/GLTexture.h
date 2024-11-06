#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <filesystem>
#include <string>

#include <glad/glad.h>

namespace GLShader
{
	class GLTexture
	{
	public:
		void SetTextureUnit(GLint unit) { TextureUnit = unit; }
		GLuint GetTextureUnit() const { return TextureUnit; }
		GLuint GetID() const { return ID; }

		void Bind();
		void Unbind();
		void Load();
		void Unload();

		void CreateTexture();

	public:
		GLTexture(std::filesystem::path path, int width, int height, int channels = 2, bool generateMipMaps = true);
		~GLTexture();

	private:
		GLint Width;
		GLint Height;
		GLint Channels;
		std::filesystem::path FilePath;



		GLuint ID = 0;
		GLint TextureUnit = 0;
		bool GenerateMipMaps;
		unsigned char* ImageData = nullptr;
		bool IsImageLoaded = false;

	};
}
#endif // !GLTEXTURE_H
