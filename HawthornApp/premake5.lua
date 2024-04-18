--HawthornApp premake5 script

project "HawthornApp"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	files { "src/**.h", "src/**.cpp" }

	includedirs
	{
		"../Hawthorn/src",

		--"../Hawthorn/vendor/tinyobjloader",

		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",

		--"%{IncludeDir.ImGui}",
		--"%{IncludeDir.glm}",

		"%{IncludeDir.VulkanSDK}",
		--"%{IncludeDir.volk}",
		--"%{IncludeDir.vma}",
		--"%{IncludeDir.fmt}",
		--"%{IncludeDir.stb}",
		--"%{IncludeDir.cli11}",
		--"%{IncludeDir.tinygltf}",
	}

	links
	{
		"Hawthorn"
	}

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	filter "system:windows"
		systemversion "latest"
		defines { "HT_PLATFORM_WINDOWS" }


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
