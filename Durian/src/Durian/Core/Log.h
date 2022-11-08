#pragma once

#if defined DURIAN_DEBUG || DURIAN_RELEASE

#include <spdlog/spdlog.h>

#define DURIAN_LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define DURIAN_LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define DURIAN_LOG_ERROR(...) spdlog::error(__VA_ARGS__)

#else

#define DURIAN_DEBUG(...)
#define DURIAN_WARN(...)
#define DURIAN_ERROR(...)

#endif