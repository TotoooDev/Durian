#include <pch.h>
#include <Durian/Graphics/Renderer.h>
#include <Panels/RendererStatsPanel.h>
#include <imgui/imgui.h>

namespace Durian
{
    void RendererStatsPanel::Draw(bool* isOpen)
    {
        ImGui::Begin("Renderer stats");
        RendererStats stats = Renderer::GetRendererStats();
        ImGui::Text("%f FPS", (1.0f / stats.FrameTime) * 1000.0f);
        ImGui::Text("Render time: %fms", stats.FrameTime);
        ImGui::Text("Num vertices: %d", stats.NumVertices);
        ImGui::Text("Num indices: %d", stats.NumIndices);
        ImGui::End();
    }
}