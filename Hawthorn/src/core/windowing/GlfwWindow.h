#pragma once

//#include "common/vk_common.h"
#include "Window.h"

struct GLFWwindow;

namespace HT
{
	class Platform;

	/**
	 * @brief An implementation of GLFW, inheriting the behaviour of the Window interface
	 */
	class GlfwWindow : public Window
	{
	public:
		GlfwWindow(Platform* platform, const Window::Properties& properties);

		virtual ~GlfwWindow();

		//VkSurfaceKHR create_surface(Instance& instance) override;

		//VkSurfaceKHR create_surface(VkInstance instance, VkPhysicalDevice physical_device) override;

		bool ShouldClose() override;

		void ProcessEvents() override;

		void Close() override;

		float GetDpiFactor() const override;

		float GetContentScaleFactor() const override;

		std::vector<const char*> GetRequiredSurfaceExtensions() const override;

	private:
		GLFWwindow* handle = nullptr;
	};
}       
