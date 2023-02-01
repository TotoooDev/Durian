#pragma once
#include <Durian/Core/Window.h>
// #include <SDL2/SDL.h>
#include <string>

namespace Durian
{
	class Texture
	{
	public:
		Texture(const std::string& path = "");
		~Texture();

		void LoadFromFile(const std::string& path);
		void Bind(unsigned int activeTexture = 0) const;
		
		unsigned int GetID() const { return m_ID; }
		std::string GetPath() const { return m_Path; }

	private:
		unsigned int m_ID;
		std::string m_Path;
	};
}