-- premake5_external.lua

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["spdlog"] = "third_party/spdlog/include"
IncludeDir["GLFW"] = "third_party/GLFW/include"

IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

-- IncludeDir["volk"] = "vendor/volk"
-- IncludeDir["vma"] = "vendor/vma/include"
-- IncludeDir["ImGui"] = "vendor/ImGui"
-- IncludeDir["glm"] = "vendor/glm"
-- IncludeDir["fmt"] = "vendor/fmt/include"
-- IncludeDir["stb"] = "vendor/stb"
-- IncludeDir["cli11"] = "vendor/cli11/include"
-- IncludeDir["tinygltf"] = "vendor/tinygltf"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"

group "ThirdParty"
	include "Hawthorn/third_party/GLFW"
-- 	include "Hawthorn/vendor/ImGui"
group ""

group "Engine"
	include "Hawthorn/premake5.lua"
group ""