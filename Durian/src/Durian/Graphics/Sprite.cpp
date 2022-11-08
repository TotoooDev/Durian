#include <pch.h>
#include <Durian/Graphics/Sprite.h>

namespace Durian
{
	Sprite::Sprite(Window* window)
		: m_Window(window)
	{

	}

	void Sprite::Draw()
	{
		if (m_Texture)
			SDL_RenderCopy(m_Window->GetRenderer(), m_Texture->GetTexture(), nullptr, &m_Rect);
	}
}