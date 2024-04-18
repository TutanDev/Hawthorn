#pragma once

#include <string>

#include <Windows.h>
#include <core/platform/Context.h>

namespace HT
{
	/**
	 * @brief MS Windows platform context
	 *
	 * @warning Use in extreme circumstances with code guarded by the PLATFORM__WINDOWS define
	 */
	class WindowsPlatformContext final : public PlatformContext
	{
	public:
		WindowsPlatformContext(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow);
		~WindowsPlatformContext() override = default;
	};
}     