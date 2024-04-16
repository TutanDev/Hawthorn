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

		-- "vendor/spdlog/include",
		-- "vendor/tinyobjloader",

		"%{IncludeDir.VulkanSDK}",
		-- "%{IncludeDir.volk}",
		-- "%{IncludeDir.vma}",
		-- "%{IncludeDir.fmt}",
		-- "%{IncludeDir.stb}",
		-- "%{IncludeDir.cli11}",
		-- "%{IncludeDir.tinygltf}",

		-- "%{IncludeDir.ImGui}",
		-- "%{IncludeDir.GLFW}",
		-- "%{IncludeDir.glm}",
	}

	links
	{
		--"GLFW",
		"%{Library.Vulkan}",
		--"ImGui"
	}

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	filter "system:windows"
		systemversion "latest"
		defines { "HT_PLATFORM_WINDOWS", "HT_BUILD_DLL", "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS" }

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