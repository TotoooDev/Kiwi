workspace "Kiwi"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Kiwi"
    location "Kiwi"
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
		"Kiwi/src",
		"Kiwi/src/Kiwi",
		"Kiwi/src/vendor"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		-- add windows specific stuff here

	filter "configurations:Debug"
		defines "KIWI_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "KIWI_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "KIWI_DIST"
		optimize "On"



project "Chinabelle"
	location "Chinabelle"
	kind "ConsoleApp"
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
		"Chinabelle/src",
		"Chinabelle/src/vendor",
		"Kiwi/src/vendor",
		"Kiwi/src"
	}

	libdirs
	{
		"libs"
	}

	links
	{
		"Kiwi",
        "SDL2"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		-- add windows specific stuff here

	filter "configurations:Debug"
		defines "KIWI_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "KIWI_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "KIWI_DIST"
		optimize "On"
