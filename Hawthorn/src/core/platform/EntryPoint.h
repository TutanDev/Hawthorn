#pragma once

#include "Context.h"

 // Platform specific entrypoint definitions
 // Applications should use CUSTOM_MAIN to define their own main function
 // Definitions added by core/CMakeLists.txt

#if defined(HT_PLATFORM_WINDOWS)
#	include <Windows.h>
std::unique_ptr<HT::PlatformContext> CreatePlatformContext(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow);

#	define CUSTOM_MAIN(context_name)                                                                    \
		int          PlatformMain(const HT::PlatformContext &);                                        \
		int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) \
		{                                                                                                \
			auto context = CreatePlatformContext(hInstance, hPrevInstance, lpCmdLine, nCmdShow);       \
			return PlatformMain(*context);                                                              \
		}                                                                                                \
		int PlatformMain(const HT::PlatformContext &context_name)
#else
#	include <stdexcept>
#	define CUSTOM_MAIN(context_name)                           \
		int main(int argc, char *argv[])                        \
		{                                                       \
			throw std::runtime_error{"platform not supported"}; \
		}                                                       \
		int unused(const HT::PlatformContext &context_name)
#endif
