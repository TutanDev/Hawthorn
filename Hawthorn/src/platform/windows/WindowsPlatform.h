#pragma once

#include "core/platform/Platform.h"

namespace HT
{
	class WindowsPlatform : public Platform
	{
	public:
		WindowsPlatform(const PlatformContext& context);

		virtual ~WindowsPlatform() = default;

	protected:
		virtual void createWindow(const Window::Properties& properties) override;
	};
}        // namespace vkb
