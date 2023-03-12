#include <pch.h>
#include <Utils/FileManagement.h>
#include <Durian/Core/Application.h>
#include <SDL2/SDL_syswm.h>
#include <string>

#ifdef DURIAN_WINDOWS
#include <commdlg.h>
#endif

#ifdef DURIAN_LINUX
#include <tinyfiledialogs/tinyfiledialogs.h>
#endif

namespace Durian
{
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

	std::string FileDialog::GetFileName()
	{
		// return ImGuiFileDialog::Instance()->GetCurrentFileName();
		return m_FilePath;
	}

	const char* FileDialog::GetDurianSceneFilter()
	{
		#ifdef DURIAN_WINDOWS
			return "Durian scene file (*.durian)\0*.durian\0";
		#endif
		#ifdef DURIAN_USE_TINYFILEDIALOGS
			return ".durian";
		#endif
		return "";
	}
	const char* FileDialog::GetImagesFilter()
	{
		// TODO: Add the other formats
		#ifdef DURIAN_WINDOWS
			return "Image files\0*.jpg;*.jpeg;*.png;*.bmp\0";
		#endif
		#ifdef DURIAN_USE_TINYFILEDIALOGS
			return ".jpg,.jpeg,.png,.bmp";
		#endif
		return "";
	}
	const char* FileDialog::GetSoundsFilter()
	{
		// TODO: Add the other formats
		#ifdef DURIAN_WINDOWS
			return "Sound files\0*.wav;*.mp3;*.ogg\0";
		#endif
		#ifdef DURIAN_USE_TINYFILEDIALOGS
			return ".wav,.mp3,.ogg";
		#endif
		return "";
	}
	const char* FileDialog::GetLuaScriptFilter()
	{
		#ifdef DURIAN_WINDOWS
			return "Lua script file\0*.lua\0";
		#endif
		#ifdef DURIAN_USE_TINYFILEDIALOGS
			return ".lua";
		#endif
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
        #ifdef DURIAN_USE_TINYFILEDIALOGS
			m_FilePath = tinyfd_saveFileDialog("Save as...", ".", 0, nullptr, nullptr);
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
		#ifdef DURIAN_USE_TINYFILEDIALOGS
			m_FilePath = tinyfd_openFileDialog("Open file...", ".", 0, nullptr, nullptr, 0);
		#endif
	}
	void FileDialog::OpenFolderDialog()
	{

	}
}
