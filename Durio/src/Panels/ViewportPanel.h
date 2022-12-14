#pragma once
#include <Durian/Core/Ref.h>
#include <Durian/Graphics/Framebuffer.h>
#include <imgui/imgui.h>

namespace Durian
{
	class ViewportPanel
	{
	public:
		ViewportPanel(Ref<Framebuffer> target = nullptr, ImVec2* viewportSize = nullptr)
			: m_Framebuffer(target), m_FramebufferSize(viewportSize) {}

		void Draw(bool* isOpen)
		{
			if (!(*isOpen))
				return;

			m_FramebufferSize->x = m_Framebuffer->GetSpec().Width;
			m_FramebufferSize->y = m_Framebuffer->GetSpec().Height;
			
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
			ImGui::Begin("Viewport", isOpen);
			ImVec2 regionAvail = ImGui::GetContentRegionAvail();
			if (m_FramebufferSize->x != regionAvail.x || m_FramebufferSize->y != regionAvail.y)
			{
				m_Framebuffer->Resize(regionAvail.x, regionAvail.y);
				*m_FramebufferSize = regionAvail;
			}
			ImGui::Image((ImTextureID)m_Framebuffer->RetrieveTexture(0), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::End();
			ImGui::PopStyleVar();
		}

		void SetFramebuffer(Ref<Framebuffer> framebuffer) { m_Framebuffer = framebuffer; }

	private:
		Ref<Framebuffer> m_Framebuffer;
		ImVec2* m_FramebufferSize;
	};
}