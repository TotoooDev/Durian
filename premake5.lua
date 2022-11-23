
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
			"SDL2_image",
			"glew32",
			"opengl32"
		}

	filter "system:linux"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		links
		{
			"SDL2",
			"SDL2main",
			"SDL2_image",
			"GLEW",
			"GL"
		}

		-- add windows specific stuff here

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
			"SDL2_image",
			"glew32",
			"opengl32"
		}

	filter "system:linux"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		links
		{
			"SDL2",
			"SDL2main",
			"SDL2_image",
			"GLEW",
			"GL"
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