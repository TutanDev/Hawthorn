#include "WindowsPlatform.h"

#include <Windows.h>
#include <iostream>
#include <shellapi.h>
#include <stdexcept>

#include "core/windowing/GlfwWindow.h"
//#include "platform/headless_window.h"

namespace HT
{
	WindowsPlatform::WindowsPlatform(const PlatformContext& context) :
		Platform(context)
	{
	}

	void WindowsPlatform::createWindow(const Window::Properties& properties)
	{
		window = std::make_unique<GlfwWindow>(this, properties);
		if (properties.mode == Window::Mode::Headless)
		{
			//window = std::make_unique<HeadlessWindow>(properties);
		}
		else
		{
			//window = std::make_unique<GlfwWindow>(this, properties);
		}
	}
} 
