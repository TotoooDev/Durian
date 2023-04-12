#pragma once
#include <Durian/Core/OS.h>
#include <string>
#include <vector>

#ifdef DURIAN_WINDOWS
#endif

namespace Durian
{
	enum class FileDialogAction
	{
		Save, Open, OpenDir
	};

	struct FileDialogFilter
	{
		std::vector<const char*> Filter;
		unsigned int NumFilters = 0;
	};

	class FileDialog
	{
	public:
		FileDialog(FileDialogAction action, FileDialogFilter filter);

		std::string GetFileName();

		static FileDialogFilter GetDurianSceneFilter();
		static FileDialogFilter GetImagesFilter();
		static FileDialogFilter GetSoundsFilter();
		static FileDialogFilter GetLuaScriptFilter();

	private:
		void SaveDialog();
		void OpenFileDialog();
		void OpenFolderDialog();

		FileDialogAction m_Action;
		FileDialogFilter m_Filter;
		std::string m_FilePath;
		std::string m_RelativePath;
	};
}
