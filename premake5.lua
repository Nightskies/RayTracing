workspace "RayTracing"
	architecture "x86_64"
	startproject "RayTracing"
	
	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glm"] = "Lib/glm"
IncludeDir["Glad"] = "Lib/Glad/include"
IncludeDir["GLFW"] = "Lib/GLFW/include"

group "Dependencies"
	include "Lib/GLFW"
	include "Lib/Glad"
group ""

project "RayTracing"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"RayTracing/**.h",
		"RayTracing/**.cpp",
		"Lib/glm/glm/**.hpp",
		"Lib/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"RayTracing",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "RAYTRACING_DEBUG_MODE"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RAYTRACING_RELEASE_MODE"
		runtime "Release"
		optimize "on"