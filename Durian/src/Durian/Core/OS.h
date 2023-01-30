#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef _WIN64
	#define DURIAN_WINDOWS
#else
	#error "Windows 32-bits is not supported!"
#endif
#elif __APPLE__
#include <TargetConditionals.h>
	#error "Apple devices are not supported!"
#elif __ANDROID__
	#error "Android is not supported!"
#elif __linux__
	#define DURIAN_LINUX
#else
	#error "Unknown compiler"
#endif
