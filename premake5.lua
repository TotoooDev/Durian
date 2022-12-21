
-- Ripped from Cherno's video on premake
-- https://www.youtube.com/watch?v=sULV3aB2qeU

workspace "Durian"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Durian"
	location "Durian"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Durian/src",
		"Durian/src/Durian",
		"Durian/src/vendor"
	}

	libdirs
	{
		"libs"
	}

	defines
	{
		"GLEW_NO_GLU"
	}

	pchheader "pch.h"
	pchsource "Durian/src/pch.cpp"

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		libdirs
		{
			"libs/windows"
		}
		links
		{
			"SDL2",
			"SDL2main",
			"glew32",
			"opengl32",
			"lua54"
		}

	filter "system:linux"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		links
		{
			"SDL2",
			"SDL2main",
			"GLEW",
			"GL",
			"lua",
			"openal",
			"sndfile"
		}

	filter "configurations:Debug"
		defines
		{
			"DURIAN_DEBUG",
			"DURIAN_DO_ASSERT",
			"DURIAN_OPENGL_DEBUG"
		}
		symbols "On"

	filter "configurations:Release"
		defines
		{
			"DURIAN_DEBUG",
			"DURIAN_DO_ASSERT",
		}
		optimize "On"

	filter "configurations:Distribution"
		defines "DURIAN_DIST"
		optimize "On"



project "Durio"
	location "Durio"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputDir .. "/%{prj.name}")

	debugdir ("bin/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Durio/src",
		"Durio/src/vendor",
		"Durian/src/vendor",
		"Durian/src"
	}

	links
	{
		"Durian",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		libdirs
		{
			"libs/windows"
		}
		links
		{
			"SDL2",
			"SDL2main",
			"SDL2_mixer",
			"glew32",
			"opengl32",
			"lua54"
		}

	filter "system:linux"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		libdirs
		{
			"libs/linux"
		}
		links
		{
			"SDL2",
			"SDL2main",
			"GLEW",
			"GL",
			"lua",
			"openal",
			"sndfile"
		}

	filter "configurations:Debug"
		defines
		{
			"DURIAN_DEBUG",
			"DURIAN_DO_ASSERT",
			"DURIAN_OPENGL_DEBUG"
		}
		symbols "On"

	filter "configurations:Release"
		defines
		{
			"DURIAN_DEBUG",
			"DURIAN_DO_ASSERT"
		}
		optimize "On"

	filter "configurations:Distribution"
		defines "DURIAN_DIST"
		optimize "On"

	postbuildcommands
	{
		"{COPYFILE} shaders/*.vert bin/" .. outputDir .. "/%{prj.name}/shaders/",
		"{COPYFILE} shaders/*.frag bin/" .. outputDir .. "/%{prj.name}/shaders/",
		"{COPYFILE} lua/DurianEngine.lua bin/" .. outputDir .. "/%{prj.name}/"
	}