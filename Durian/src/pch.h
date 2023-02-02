// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#include <Durian/Core/OS.h>

// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
#define NOMINMAX

// For stb_image
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <fstream>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <nlohmann/json.hpp>

#if defined DURIAN_WINDOWS
#include <windows.h>
#endif

#include <glm/glm.hpp>

#include <Durian/Core/Log.h>
#include <Durian/Core/Ref.h>

#endif //PCH_H
