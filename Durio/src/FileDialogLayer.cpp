#include <FileDialogLayer.h>
#include <imgui/imgui.h>

namespace Durian
{
    FileDialogLayer::FileDialogLayer(FileDialogAction action, std::string* path)
        : m_Action(action)
    {}

    void FileDialogLayer::OnImGuiRender()
    {
        ImGui::Begin("Open file...");

        ImGui::End();
    }
}