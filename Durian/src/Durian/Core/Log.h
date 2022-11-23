#pragma once
#include <signal.h>

#if defined DURIAN_DEBUG || DURIAN_RELEASE

#include <spdlog/spdlog.h>

#define DURIAN_LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define DURIAN_LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define DURIAN_LOG_ERROR(...) spdlog::error(__VA_ARGS__)

#else

#define DURIAN_LOG_INFO(...)
#define DURIAN_LOG_WARN(...)
#define DURIAN_LOG_ERROR(...)

#endif

#if defined DURIAN_DO_ASSERT

#if defined _WIN32
#define DURIAN_ASSERT(x, ...) if (!x) { DURIAN_LOG_ERROR(__VA_ARGS__); __debugbreak(); }
#elif __linux__
#define DURIAN_ASSERT(x, ...) if (!x) { DURIAN_LOG_ERROR(__VA_ARGS__); raise(SIGTRAP); }
#endif

#else

#define DURIAN_ASSERT(x, ...)

#endif