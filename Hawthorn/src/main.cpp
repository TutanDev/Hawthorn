#include "core/util/Logger.h"
#include "core/platform/Platform.h"

#include <core/platform/EntryPoint.h>
//#include <filesystem/filesystem.hpp>

#if defined(HT_PLATFORM_WINDOWS)
#	include "platform/windows/WindowsPlatform.h"
#endif

CUSTOM_MAIN(context)
{
	//HT::Filesystem::init_with_context(context);

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