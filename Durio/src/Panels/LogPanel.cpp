#include <pch.h>
#include <Panels/LogPanel.h>
#include <cstdarg>

namespace Durian
{
    LogPanel::LogPanel()
    {
        m_AutoScroll = true;
        Clear();
    }

    void LogPanel::Draw(bool* isOpen)
    {
        if (!(*isOpen))
            return;

        ImGui::Begin("Logs", isOpen);

        // Options menu
        if (ImGui::BeginPopup("Options"))
        {
            ImGui::Checkbox("Auto scroll", &m_AutoScroll);
            ImGui::EndPopup();
        }

        // Main window
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        bool clear = ImGui::Button("Clear");
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        m_Filter.Draw("Filter", -100.0f);

        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        if (clear)
            Clear();
        if (copy)
            ImGui::LogToClipboard();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        const char* buf = m_Buf.begin();
        const char* buf_end = m_Buf.end();
        if (m_Filter.IsActive())
        {
            // In this example we don't use the clipper when Filter is enabled.
            // This is because we don't have a random access on the result on our filter.
            // A real application processing logs with ten of thousands of entries may want to store the result of
            // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
            for (int line_no = 0; line_no < m_LineOffsets.Size; line_no++)
            {
                const char* line_start = buf + m_LineOffsets[line_no];
                const char* line_end = (line_no + 1 < m_LineOffsets.Size) ? (buf + m_LineOffsets[line_no + 1] - 1) : buf_end;
                if (m_Filter.PassFilter(line_start, line_end))
                    ImGui::TextUnformatted(line_start, line_end);
            }
        }
        else
        {
            // The simplest and easy way to display the entire buffer:
            //   ImGui::TextUnformatted(buf_begin, buf_end);
            // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
            // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
            // within the visible area.
            // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
            // on your side is recommended. Using ImGuiListClipper requires
            // - A) random access into your data
            // - B) items all being the  same height,
            // both of which we can handle since we an array pointing to the beginning of each line of text.
            // When using the filter (in the block of code above) we don't have random access into the data to display
            // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
            // it possible (and would be recommended if you want to search through tens of thousands of entries).
            ImGuiListClipper clipper;
            clipper.Begin(m_LineOffsets.Size);
            while (clipper.Step())
            {
                for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                {
                    const char* line_start = buf + m_LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < m_LineOffsets.Size) ? (buf + m_LineOffsets[line_no + 1] - 1) : buf_end;
                    ImGui::TextUnformatted(line_start, line_end);
                }
            }
            clipper.End();
        }
        ImGui::PopStyleVar();

        if (m_AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();
        ImGui::End();
    }

    void LogPanel::Clear()
    {
        m_Buf.clear();
        m_LineOffsets.clear();
        m_LineOffsets.push_back(0);
    }

    void LogPanel::AddLog(std::string log, ...)
    {
        int oldSize = m_Buf.size();
        va_list args;
        va_start(args, log);
        m_Buf.appendfv(log.c_str(), args);
        va_end(args);
        for (int newSize = m_Buf.size(); oldSize < newSize; oldSize++)
        {
            if (m_Buf[oldSize] == '\n')
                m_LineOffsets.push_back(oldSize + 1);
        }
    }
}