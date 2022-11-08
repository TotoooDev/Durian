#include <pch.h>
#include <Durian/Graphics/Sprite.h>

namespace Durian
{
	Sprite::Sprite(Window* window)
		: m_Window(window)
	{

	}

	void Sprite::LoadTexture(const std::string& path)
	{
		if (!m_Texture)
			m_Texture = CreateRef<Texture>(m_Window, path);
		else
			m_Texture->LoadFromFile(path);
	}

	void Sprite::Draw()
	{
		if (m_Texture)
		{
			SDL_FRect rect = { Pos.x, Pos.y, Scale.x, Scale.y };
			SDL_FPoint rotationCenter = { Scale.x * RotationCenter.x, Scale.y * RotationCenter.y };
			SDL_RenderCopyExF(m_Window->GetRenderer(), m_Texture->GetTexture(), nullptr, &rect, Rotation, &rotationCenter, (SDL_RendererFlip)Flip);
		}
	}
}