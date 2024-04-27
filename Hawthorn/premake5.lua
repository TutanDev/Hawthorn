-- Hawthorn premake5 script

project "Hawthorn"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

   files { "src/**.h", "src/**.cpp" }

	includedirs
	{
		"src",

		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		-- "vendor/tinyobjloader",

		"%{IncludeDir.VulkanSDK}",
		-- "%{IncludeDir.volk}",
		-- "%{IncludeDir.vma}",
		-- "%{IncludeDir.fmt}",
		-- "%{IncludeDir.stb}",
		-- "%{IncludeDir.cli11}",
		-- "%{IncludeDir.tinygltf}",

	}

	links
	{
		"%{Library.Vulkan}",
		"GLFW",
		"ImGui"
	}

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")


	defines { "GLM_FORCE_SWIZZLE", "GLM_FORCE_RADIANS", "GLM_FORCE_CTOR_INIT", "GLM_ENABLE_EXPERIMENTAL"}

	filter "system:windows"
		systemversion "latest"
		defines { "HT_PLATFORM_WINDOWS", "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS" }

	filter "configurations:Debug"
		defines {"HT_DEBUG", "HT_ENABLE_ASSERTS"}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines { "HT_RELEASE" }
		runtime "Release"
		optimize "on"
		symbols "on"

	filter "configurations:Dist"
		defines { "HT_DIST" }
		runtime "Release"
		optimize "on"
		symbols "off"