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
		FileDialog(FileDialogAction action, const char* filter = "");

		std::string GetPath();
		std::string GetObjectName();

	private:
		void SaveDialog();
		void OpenFileDialog();
		void OpenFolderDialog();

		FileDialogAction m_Action;
		const char* m_Filter;
		std::string m_FilePath;

		#ifdef DURIAN_LINUX
			bool m_IsWindowOpen;
		#endif
	};
}
