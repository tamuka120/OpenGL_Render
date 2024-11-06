#include "GLTexture.h"

#include "stb_image/stb_image.h"
#include "spdlog/spdlog.h"

void GLShader::GLTexture::Bind()
{
	if(!IsImageLoaded)
	{
		return;
	}
	glActiveTexture(TextureUnit); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, ID);
}

void GLShader::GLTexture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GLShader::GLTexture::Load()
{
	// OpenGL expects the 0.0 coordinate on the y-axis to be on the bottom side
	stbi_set_flip_vertically_on_load(true);

	auto data = stbi_load(FilePath.string().c_str(), &Width, &Height, &Channels, 0);
	if(data != nullptr)
	{
		IsImageLoaded = true;
		ImageData = data;
		return;
	}

	spdlog::critical("Failed to load texture {}", FilePath.string());
}

void GLShader::GLTexture::Unload()
{
	if(ImageData)
	{
		stbi_image_free(ImageData);
	}
}

void GLShader::GLTexture::CreateTexture()
{
	if (!IsImageLoaded) 
	{
		return;
	}


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, ImageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if(GenerateMipMaps)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

}

GLShader::GLTexture::GLTexture(std::filesystem::path path, int width, int height, int channels, bool generateMipMaps) :
	FilePath(path),
	Width(width),
	Height(height),
	Channels(channels),
	GenerateMipMaps(generateMipMaps)
{
	glGenTextures(1, &ID);
	Load();
}

GLShader::GLTexture::~GLTexture()
{
	Unload();
	Unbind();
}
