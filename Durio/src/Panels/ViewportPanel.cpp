#include <pch.h>
#include <Panels/ViewportPanel.h>

namespace Durian
{
	ViewportPanel::ViewportPanel(Ref<Framebuffer> target, ImVec2* viewportSize, bool* hovered)
		: m_Framebuffer(target), m_FramebufferSize(viewportSize), m_Hovered(hovered) {}

	void ViewportPanel::Draw(bool* isOpen)
	{
		if (!(*isOpen))
			return;

		m_FramebufferSize->x = m_Framebuffer->GetSpec().Width;
		m_FramebufferSize->y = m_Framebuffer->GetSpec().Height;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		ImGui::Begin(m_Title.c_str(), isOpen);
		*m_Hovered = ImGui::IsWindowHovered();
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
}