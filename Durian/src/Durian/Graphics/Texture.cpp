#include <pch.h>
#include <Durian/Graphics/Texture.h>
#include <SDL2/SDL_image.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GL/GL.h>

namespace Durian
{
	Texture::Texture(Window* window, const std::string& path)
		: m_Window(window)
	{
		LoadFromFile(path);
	}

	Texture::~Texture()
	{
		SDL_DestroyTexture(m_Texture);
	}

	void Texture::LoadFromFile(const std::string& path)
	{
		if (path.empty())
			return;

		// int width, height, nbLevels;
		// unsigned char* data = stbi_load(path.c_str(), &width, &height, &nbLevels, 0);
		// if (!data)
		// {
		// 	DURIAN_LOG_ERROR("Failed to load file {0}!", path);
		// 	return;
		// }
		// 
		// glGenTextures(1, &m_ID);
		// glBindTexture(GL_TEXTURE_2D, m_ID);

		m_Texture = IMG_LoadTexture(m_Window->GetRenderer(), path.c_str());
		if (!m_Texture)
		{
			DURIAN_LOG_ERROR("IMG failed to load file {0}!", path);
			DURIAN_LOG_INFO("IMG error: ", IMG_GetError());
		}
	}
}