#pragma once
#include <Durian/Core/OS.h>

#ifdef DURIAN_WINDOWS
#endif

namespace Durian
{
	namespace Utils
	{
		std::string SaveFileDialog(const char* filter);
		std::string OpenFileDialog(const char* filter);
	}
}