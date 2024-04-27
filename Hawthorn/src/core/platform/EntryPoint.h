#pragma once

#include "PlatformContext.h"

 // Platform specific entrypoint definitions
 // Applications should use CUSTOM_MAIN to define their own main function
 // Definitions added by core/CMakeLists.txt

//#if defined(HT_PLATFORM_WINDOWS)
//#	include <Windows.h>
//extern std::unique_ptr<HT::PlatformContext> CreatePlatformContext(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow);
//
//#	define CUSTOM_MAIN(context_name)                                                                    \
//		int          PlatformMain(const HT::PlatformContext &);                                        \
//		int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) \
//		{                                                                                                \
//			auto context = CreatePlatformContext(hInstance, hPrevInstance, lpCmdLine, nCmdShow);       \
//			return PlatformMain(*context);                                                              \
//		}                                                                                                \
//		int PlatformMain(const HT::PlatformContext &context_name)
//#else
//#	include <stdexcept>
//#	define CUSTOM_MAIN(context_name)                           \
//		int main(int argc, char *argv[])                        \
//		{                                                       \
//			throw std::runtime_error{"platform not supported"}; \
//		}                                                       \
//		int unused(const HT::PlatformContext &context_name)
//#endif

#include "core/util/Logger.h"
#include "core/platform/Platform.h"

#include <core/file_system/FileSystem.h>

#if defined(HT_PLATFORM_WINDOWS)
#	include <Windows.h>
#	include "platform/windows/WindowsContext.h"
#	include "platform/windows/WindowsPlatform.h"
#endif

int CustomMain(const HT::PlatformContext& context)
{
	HT::FS::init_with_context(context);

#if defined(HT_PLATFORM_WINDOWS)
	HT::WindowsPlatform platform{ context };
#endif

	//auto code = platform.initialize(plugins::get_all());
	auto code = platform.Initialize();

	if (code == HT::ExitCode::Success)
	{
		code = platform.MainLoop();
	}

	platform.Terminate(code);

	return 0;
}

#if defined(HT_PLATFORM_WINDOWS)
	int main(int argc, char* argv[])                        
	{                                                       
		auto context = std::make_unique<HT::WindowsPlatformContext>();
		return CustomMain(*context);
	}
#endif

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) \
//{
//	auto context = std::make_unique<HT::WindowsPlatformContext>(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
//	return CustomMain(*context);
//}

