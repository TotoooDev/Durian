#include <pch.h>
#include <Durian/Utils/FileManagement.h>
#include <Durian/Core/Application.h>
#include <SDL2/SDL_syswm.h>
#include <string>

#ifdef DURIAN_WINDOWS
#include <commdlg.h>
#endif

#ifdef DURIAN_LINUX
#include <ImGuiFileDialog/ImGuiFileDialog.h>
#endif

namespace Durian
{
	FileDialog::FileDialog(FileDialogAction action, const char* filter)
		: m_Action(action)
	{
		#ifdef DURIAN_USE_IMGUI_DIALOGS
			// Trim the filter string for ImGuiFileDialog because it takes only the extension
			int i;
			for (i = 0; i < 1024; i++)
			{
				if (filter[i] == '\0')
					break;
			}
			m_Filter = &filter[i + 1]; // Dangerous but C++ wouldn't be fun without segfaults
		#else
			m_Filter = filter;
		#endif

		switch (action)
		{
		case FileDialogAction::Open:
			OpenFileDialog();
			break;
		case FileDialogAction::OpenDir:
			OpenFolderDialog();
			break;
		case FileDialogAction::Save:
			SaveDialog();
			break;
		}
	}

	std::string FileDialog::GetPath()
	{
		return ImGuiFileDialog::Instance()->GetFilePathName();
	}

	std::string FileDialog::GetObjectName()
	{
		return "";
	}

	void FileDialog::SaveDialog()
	{
	#ifdef DURIAN_WINDOWS
			SDL_SysWMinfo wmInfo;
			SDL_VERSION(&wmInfo.version);
			if (SDL_GetWindowWMInfo(Application::Get().GetWindowSpec().NativeWindow, &wmInfo) == SDL_FALSE)
				DURIAN_LOG_ERROR(SDL_GetError());
			HWND hwnd = wmInfo.info.win.window;

			OPENFILENAMEA openFileName;
			CHAR szFile[260] = { 0 };
			ZeroMemory(&openFileName, sizeof(OPENFILENAME));
			openFileName.lStructSize = sizeof(OPENFILENAME);
			openFileName.hwndOwner = hwnd;
			openFileName.lpstrFile = szFile;
			openFileName.nMaxFile = sizeof(szFile);
			openFileName.lpstrFilter = m_Filter;
			openFileName.nFilterIndex = 1;
			openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
			if (GetSaveFileNameA(&openFileName) == TRUE)
			{
				m_FilePath = openFileName.lpstrFile;
			}
		#endif
        #ifdef DURIAN_USE_IMGUI_DIALOGS
			DURIAN_LOG_INFO("poggers");
		#endif
	}

	void FileDialog::OpenFileDialog()
	{
	#ifdef DURIAN_WINDOWS
			SDL_SysWMinfo wmInfo;
			SDL_VERSION(&wmInfo.version);
			if (SDL_GetWindowWMInfo(Application::Get().GetWindowSpec().NativeWindow, &wmInfo) == SDL_FALSE)
				DURIAN_LOG_ERROR(SDL_GetError());
			HWND hwnd = wmInfo.info.win.window;
			
			OPENFILENAMEA openFileName;
			CHAR szFile[260] = { 0 };
			ZeroMemory(&openFileName, sizeof(OPENFILENAME));
			openFileName.lStructSize = sizeof(OPENFILENAME);
			openFileName.hwndOwner = hwnd;
			openFileName.lpstrFile = szFile;
			openFileName.nMaxFile = sizeof(szFile);
			openFileName.lpstrFilter = m_Filter;
			openFileName.nFilterIndex = 1;
			openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
			if (GetOpenFileNameA(&openFileName) == TRUE)
			{
				m_FilePath = openFileName.lpstrFile;
            }
		#endif
		#ifdef DURIAN_USE_IMGUI_DIALOGS
			ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Open file...", m_Filter, ".");
		#endif
	}
	void FileDialog::OpenFolderDialog()
	{

	}
}
