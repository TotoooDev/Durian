#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <pch.h>
#include <Durian/Graphics/Texture.h>
#include <GL/glew.h>

namespace Durian
{
	Texture::Texture(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(true);
		glGenTextures(1, &m_ID);
		LoadFromFile(path);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_ID);
	}

	void Texture::LoadFromFile(const std::string& path)
	{
		if (path.empty())
			return;
		
		glBindTexture(GL_TEXTURE_2D, m_ID);

		// Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		int width, height, numChannels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
		if (data == nullptr)
		{
			DURIAN_LOG_ERROR("Failed to load file {0}!", path);
			return;
		}

		GLenum format = GL_RGB;
		if (numChannels == 3)
			format = GL_RGB;
		if (numChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		// glGenerateMipmap(GL_TEXTURE_2D); // Crashes for no fucking reason and I can't figure out why

		stbi_image_free(data);
	}

	void Texture::Bind(unsigned int activeTexture)
	{
		glActiveTexture(GL_TEXTURE0 + activeTexture);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}