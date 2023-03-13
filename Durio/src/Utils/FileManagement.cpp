#include <pch.h>
#include <Utils/FileManagement.h>
#include <Durian/Core/Application.h>
#include <SDL2/SDL_syswm.h>
#include <string>

#ifdef DURIAN_WINDOWS
#include <commdlg.h>
#endif

#ifdef DURIAN_USE_TINYFILEDIALOGS
#include <tinyfiledialogs/tinyfiledialogs.h>
#endif

namespace Durian
{
	FileDialog::FileDialog(FileDialogAction action, FileDialogFilter filter)
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

	std::string FileDialog::GetFileName()
	{
		return m_FilePath;
	}

	FileDialogFilter FileDialog::GetDurianSceneFilter()
	{
		#ifdef DURIAN_WINDOWS
			return { {"Durian scene file (*.durian)\0*.durian\0"}, 1 };
		#endif
		#ifdef DURIAN_USE_TINYFILEDIALOGS
			return { {"*.durian"}, 1 };
		#endif
		return {};
	}
	FileDialogFilter FileDialog::GetImagesFilter()
	{
		// TODO: Add the other formats
		#ifdef DURIAN_WINDOWS
			return { {"Image files\0*.jpg;*.jpeg;*.png;*.bmp\0"}, 4 };
		#endif
		#ifdef DURIAN_USE_TINYFILEDIALOGS
			return { {"*.jpg","*.jpeg","*.png","*.bmp"}, 4 };
		#endif
		return {};
	}
	FileDialogFilter FileDialog::GetSoundsFilter()
	{
		// TODO: Add the other formats
		#ifdef DURIAN_WINDOWS
			return { {"Sound files\0*.wav;*.mp3;*.ogg\0"}, 3 };
		#endif
		#ifdef DURIAN_USE_TINYFILEDIALOGS
			return { {"*.wav","*.mp3","*.ogg"}, 3 };
		#endif
		return {};
	}
	FileDialogFilter FileDialog::GetLuaScriptFilter()
	{
		#ifdef DURIAN_WINDOWS
			return { {"Lua script file\0*.lua\0"}, 1 };
		#endif
		#ifdef DURIAN_USE_TINYFILEDIALOGS
			return { {"*.lua"}, 1 };
		#endif
		return {};
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
			openFileName.lpstrFilter = m_Filter.Filter[0];
			openFileName.nFilterIndex = 1;
			openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
			if (GetSaveFileNameA(&openFileName) == TRUE)
			{
				m_FilePath = openFileName.lpstrFile;
			}
		#endif
        #ifdef DURIAN_USE_TINYFILEDIALOGS
			const char* path = tinyfd_saveFileDialog("Save as...", ".", m_Filter.NumFilters, m_Filter.Filter.data(), nullptr);
			if (path != nullptr)
				m_FilePath = path;
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
			openFileName.lpstrFilter = m_Filter.Filter[0];
			openFileName.nFilterIndex = 1;
			openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
			if (GetOpenFileNameA(&openFileName) == TRUE)
			{
				m_FilePath = openFileName.lpstrFile;
				DURIAN_LOG_INFO("Opening {}", m_FilePath);
            }
		#endif
		#ifdef DURIAN_USE_TINYFILEDIALOGS
			const char* path =  tinyfd_openFileDialog("Open file...", ".", m_Filter.NumFilters, m_Filter.Filter.data(), nullptr, 0);
			if (path != nullptr)
			{
				m_FilePath = path;
				DURIAN_LOG_INFO("Opening {}", m_FilePath);
			}
		#endif
	}
	void FileDialog::OpenFolderDialog()
	{

	}
}
