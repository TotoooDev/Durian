#include <pch.h>
#include <Durian/Graphics/Texture.h>
#include <SDL2/SDL_image.h>

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

		m_Texture = IMG_LoadTexture(m_Window->GetRenderer(), path.c_str());
		if (!m_Texture)
		{
			DURIAN_LOG_ERROR("IMG failed to load file {0}!", path);
			DURIAN_LOG_INFO("IMG error: ", IMG_GetError());
		}
	}
}