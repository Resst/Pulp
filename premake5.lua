workspace "Pulp"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Pulp/vendor/GLFW/include"
IncludeDir["Glad"] = "Pulp/vendor/Glad/include"
IncludeDir["glm"] = "Pulp/vendor/glm"
group "Dependencies"
	include "Pulp/vendor/GLFW"
	include "Pulp/vendor/Glad"
group ""


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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}"
	}

	links{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"PLP_PLATFORM_WINDOWS",
			"PLP_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\""),
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Tests/\"")
		}

	filter "configurations:Debug"
		defines "PLP_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "PLP_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines "PLP_DIST"
		buildoptions "/MD"
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
		"Pulp/src",
		"%{IncludeDir.glm}"
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
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "PLP_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines "PLP_DIST"
		buildoptions "/MD"
		optimize "On"




