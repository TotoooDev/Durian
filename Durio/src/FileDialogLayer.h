#pragma once
#include <Durian/Core/Layer.h>
#include <string>

namespace Durian
{
    enum class FileDialogAction
    {
        Save, OpenFile, OpenFolder
    };

    class FileDialogLayer : public Layer
    {
    public:
        FileDialogLayer(FileDialogAction action, std::string* path);

        void OnCreate() override {}
		void OnUpdate(double timestep) override {}
		void OnImGuiRender() override;

    private:
        FileDialogAction m_Action;
        std::string* m_Path;
    };
}