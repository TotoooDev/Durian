#pragma once
#include <Durian/Core/OS.h>
#include <string>

#ifdef DURIAN_WINDOWS
#endif

namespace Durian
{
	enum class FileDialogAction
	{
		Save, Open, OpenDir
	};

	class FileDialog
	{
	public:
		FileDialog(FileDialogAction action, const char* filter = "");

		std::string GetFileName();

		static const char* GetDurianSceneFilter();
		static const char* GetImagesFilter();
		static const char* GetSoundsFilter();
		static const char* GetLuaScriptFilter();

	private:
		void SaveDialog();
		void OpenFileDialog();
		void OpenFolderDialog();

		FileDialogAction m_Action;
		const char* m_Filter;
		std::string m_FilePath;
	};
}
