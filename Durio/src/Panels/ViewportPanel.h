#pragma once
#include <Durian/Core/Ref.h>
#include <Durian/Graphics/Framebuffer.h>
#include <imgui/imgui.h>

namespace Durian
{
	class ViewportPanel
	{
	public:
		ViewportPanel(Ref<Framebuffer> target = nullptr, ImVec2* viewportSize = nullptr, bool* hovered = nullptr);

		void Draw(bool* isOpen);

		void SetFramebuffer(Ref<Framebuffer> framebuffer) { m_Framebuffer = framebuffer; }
		void SetTitle(const std::string& title) { m_Title = title; }

	private:
		Ref<Framebuffer> m_Framebuffer;
		ImVec2* m_FramebufferSize;
		std::string m_Title = "Viewport";
		bool* m_Hovered;
	};
}