#include "core/platform/Entrypoint.h"

#include "WindowsContext.h"
#include <Windows.h>

std::unique_ptr<HT::PlatformContext> CreatePlatformContext(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	return std::make_unique<HT::WindowsPlatformContext>(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
