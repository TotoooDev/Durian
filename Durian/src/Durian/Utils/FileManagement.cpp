#include <pch.h>
#include <Durian/Utils/FileManagement.h>
#include <Durian/Core/Application.h>
#include <SDL2/SDL_syswm.h>
#include <string>
#include <commdlg.h>

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
				return "";
			#endif
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
				return "";
			#endif
		}
	}
}