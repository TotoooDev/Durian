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

	startproject "Durio"

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Durian"
	location "Durian"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	
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

	defines ("GLEW_NO_GLU")

	pchheader "pch.h"
	pchsource "Durian/src/pch.cpp"

	filter "files:Durian/src/vendor/tinyfiledialogs/tinyfiledialogs.c"
		flags "NoPCH"

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
		libdirs ("libs/windows")

		links
		{
			"Comdlg32",
			"Ole32",
			"SDL2",
			"SDL2main",
			"glew32",
			"opengl32",
			"OpenAL32",
			"sndfile"
		}

	filter "system:linux"
		staticruntime "On"
		systemversion "latest"
		libdirs ("libs/linux")

		links
		{
			"SDL2",
			"SDL2main",
			"GLEW",
			"GL",
			"openal",
			"sndfile",
            "vorbis",
            "vorbisfile",
			"lua"
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


project "DurianLua"
	location "DurianLua"
	kind "SharedLib"
	language "C"
	cppdialect "C++17"

	targetname ("Durian")
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
		"DurianLua/src",
		"DurianLua/src/vendor",
		"Durian/src",
		"Durian/src/vendor",
		"Durian/src/Durian"
	}

	filter "system:windows"
		libdirs ("libs/windows")
		links
		{
			"lua54"
		}

	filter "system:linux"
		libdirs ("libs/linux")
		links ("lua")
		postbuildcommands
		{
			"mv ../bin/" .. outputDir .. "/%{prj.name}/libDurian.so ../bin/" .. outputDir .. "/%{prj.name}/Durian.so",
			"cp ../bin/" .. outputDir .. "/%{prj.name}/Durian.so ../bin/Debug-linux-x86_64/Durio --recursive"
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


project "Durio"
	location "Durio"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

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
		"Durian"
	}
	
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
		libdirs ("libs/windows")

		links
		{
			"SDL2",
			"SDL2main",
			"SDL2_mixer",
			"glew32",
			"opengl32",
			"OpenAL32",
			"sndfile",
			"lua54"
		}
		postbuildcommands ("xcopy ..\\dev-assets ..\\bin\\" .. outputDir .. "\\%{prj.name}\\ /s /e /y /i")

	filter "system:linux"
		staticruntime "On"
		systemversion "latest"
		libdirs ("libs/linux")

		links
		{
			"SDL2",
			"SDL2main",
			"GLEW",
			"GL",
			"openal",
			"sndfile",
            "vorbis",
            "vorbisfile",
			"lua"
		}
		postbuildcommands
		{
			"cp ../dev-assets/* ../bin/" .. outputDir .. "/%{prj.name} --recursive",
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
