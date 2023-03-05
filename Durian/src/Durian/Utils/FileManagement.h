#pragma once
#include <Durian/Core/OS.h>
#include <string>

#ifdef DURIAN_WINDOWS
#endif

namespace Durian
{
	namespace Utils
	{
		std::string SaveFileDialog(const char* filter);
		std::string OpenFileDialog(const char* filter);
	}

	enum class FileDialogAction
	{
		Save, Open, OpenDir
	};

	class FileDialog
	{
	public:
		FileDialog(FileDialogAction action, const std::string& filter = "");

		std::string GetPath() { return m_FilePath; }
		std::string GetObjectName();

	private:
		void SaveDialog();
		void OpenFileDialog();
		void OpenFolderDialog();

		FileDialogAction m_Action;
		std::string m_Filter;
		std::string m_FilePath;

		#ifdef DURIAN_LINUX
			bool m_IsWindowOpen;
		#endif
	};
}
