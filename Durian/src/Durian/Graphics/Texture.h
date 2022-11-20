#pragma once

#include <Durian/Core/Window.h>
// #include <SDL2/SDL.h>
#include <string>

namespace Durian
{
	class Texture
	{
	public:
		Texture(Window* window, const std::string& path = "");
		~Texture();

		void LoadFromFile(const std::string& path);
		void Bind(unsigned int activeTexture = 0);
		
		// SDL_Texture* GetTexture() { return m_Texture; }
		unsigned int GetID() { return m_ID; }

	private:
		// SDL_Texture* m_Texture;
		Window* m_Window;

		unsigned int m_ID;
	};
}