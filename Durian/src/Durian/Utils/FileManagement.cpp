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
	namespace Utils
	{
		std::string SaveFileDialog(const char* filter)
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
				openFileName.lpstrFilter = filter;
				openFileName.nFilterIndex = 1;
				openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
				if (GetSaveFileNameA(&openFileName) == TRUE)
				{
					return openFileName.lpstrFile;
				}
			#endif
            #ifdef DURIAN_LINUX
				DURIAN_LOG_INFO("poggers");
			#endif
			return "";
		}

		std::string OpenFileDialog(const char* filter)
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
				openFileName.lpstrFilter = filter;
				openFileName.nFilterIndex = 1;
				openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
				if (GetOpenFileNameA(&openFileName) == TRUE)
				{
					return openFileName.lpstrFile;
                }
			#endif
			#ifdef DURIAN_LINUX
				DURIAN_LOG_INFO("poggers");
				ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Open file...", "", ".");
				while (ImGuiFileDialog::Instance()->IsOpened("ChooseFileDlgKey"))
				{
					if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
					{
						// action if OK
    					if (ImGuiFileDialog::Instance()->IsOk())
    					{
    					  std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
    					  std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
    					  // action
    					}
					}
				}
				ImGuiFileDialog::Instance()->Close();
			#endif
            return "";
		}
	}

	FileDialog::FileDialog(FileDialogAction action, const char* filter)
		: m_Action(action), m_Filter(filter)
	{
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
        #ifdef DURIAN_LINUX
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
		#ifdef DURIAN_LINUX
			ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Open file...", m_Filter.c_str(), ".");
			if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey", 32, ImVec2(800.0f, 600.0f)))
			{
				DURIAN_LOG_INFO("proute");
				// action if OK
				if (ImGuiFileDialog::Instance()->IsOk())
				{
					DURIAN_LOG_INFO("pouf");
					std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
					std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
					// action
				}
				ImGuiFileDialog::Instance()->Close();
			}
		#endif
	}
	void FileDialog::OpenFolderDialog()
	{

	}
}
