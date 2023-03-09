#pragma once
#include <imgui/imgui.h>
#include <string>

namespace Durian
{
	// Shamelessly stolen from the demo
	class LogPanel
	{
	public:
		LogPanel();

		void Draw(bool* isOpen);

        void Clear();
        void AddLog(std::string log, ...);

	private:
		ImGuiTextBuffer m_Buf;
		ImGuiTextFilter m_Filter;
		ImVector<int> m_LineOffsets;
		bool m_AutoScroll;
	};
}