workspace "Pulp"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Pulp"
	location "Pulp"
	kind "SharedLib"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "plppch.h"
	pchsource "Pulp/src/plppch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"PLP_PLATFORM_WINDOWS",
			"PLP_BUILD_DLL"
		}
		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "PLP_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "PLP_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "PLP_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"Pulp/vendor/spdlog/include",
		"Pulp/src"
	}

	links{
		"Pulp"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"PLP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PLP_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "PLP_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "PLP_DIST"
		optimize "On"
