#include "Platform.h"

#include <algorithm>
#include <ctime>
#include <mutex>
#include <vector>

//#include <fmt/format.h>
#include <spdlog/async_logger.h>
#include <spdlog/details/thread_pool.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "core/util/Logger.h"
//#include "filesystem/legacy.h"
//#include "force_close/force_close.h"
//#include "platform/parsers/CLI11.h"
//#include "platform/plugins/plugin.h"
//#include "vulkan_sample.h"

//namespace plugins
//{
//	class BenchmarkMode;
//}

namespace HT
{
	const uint32_t Platform::MIN_WINDOW_WIDTH = 420;
	const uint32_t Platform::MIN_WINDOW_HEIGHT = 320;

	std::string Platform::external_storage_directory = "";

	std::string Platform::temp_directory = "";

	Platform::Platform(const PlatformContext& context)
	{
		arguments = context.Arguments();

		external_storage_directory = context.ExternalStorageDirectory();
		temp_directory = context.TempDirectory();
	}

	
	ExitCode Platform::Initialize()
	{
		// Logger
		auto sinks = GetPlatformSinks();

		auto logger = std::make_shared<spdlog::logger>("logger", sinks.begin(), sinks.end());

#ifdef HT_DEBUG
		logger->set_level(spdlog::level::debug);
#else
		logger->set_level(spdlog::level::info);
#endif

		logger->set_pattern(LOGGER_FORMAT);
		spdlog::set_default_logger(logger);

		LOGI("Logger initialized");

		// Plugins
		
		// App
		GetAppInfo(*this);

		// Window
		createWindow(window_properties);

		if (!window)
		{
			LOGE("Window creation failed!");
			return ExitCode::FatalError;
		}

		return ExitCode::Success;
	}

	ExitCode Platform::MainLoopFrame()
	{
		if (!window->ShouldClose() && !close_requested)
		{
			try
			{
				// Load the requested app
				if (NeedsToLoadApp())
				{
					if (!StartApp())
					{
						LOGE("Failed to load requested application");
						return ExitCode::FatalError;
					}

					// Compensate for load times of the app by rendering the first frame pre-emptively
					timer.Tick<Timer::Seconds>();
					active_app->Update(0.01667f);
				}

				Update();

				if (active_app && active_app->ShouldClose())
				{
					std::string id = active_app->GetName();
					on_app_close(id);
					active_app->Finish();
				}

				window->ProcessEvents();
			}
			catch (std::exception& e)
			{
				LOGE("Error Message: {}", e.what());
				LOGE("Failed when running application {}", active_app->GetName());

				on_app_error(active_app->GetName());

				return ExitCode::FatalError;
			}
		}

		return ExitCode::Success;
	}

	ExitCode Platform::MainLoop ()
	{
		while (!window->ShouldClose() && !close_requested)
		{
			try
			{
				// Load the requested app
				if (NeedsToLoadApp())
				{
					if (!StartApp())
					{
						LOGE("Failed to load requested application");
						return ExitCode::FatalError;
					}

					// Compensate for load times of the app by rendering the first frame pre-emptively
					timer.Tick<Timer::Seconds>();
					active_app->Update(0.01667f);
				}
				

				Update();

				if (active_app && active_app->ShouldClose())
				{
					std::string id = active_app->GetName();
					on_app_close(id);
					active_app->Finish();
				}

				window->ProcessEvents();
			}
			catch (std::exception& e)
			{
				LOGE("Error Message: {}", e.what());
				LOGE("Failed when running application {}", active_app->GetName());

				on_app_error(active_app->GetName());

				return ExitCode::FatalError;
			}
		}

		return ExitCode::Success;
	}

	void Platform::Update()
	{
		auto delta_time = static_cast<float>(timer.Tick<Timer::Seconds>());

		if (focused)
		{
			on_update(delta_time);

			//if (fixed_simulation_fps)
			//{
			//	delta_time = simulation_frame_time;
			//}

			//active_app->update_overlay(delta_time, [=]() {
			//	on_update_ui_overlay(*active_app->get_drawer());
			//	});
			//active_app->update(delta_time);

			//if (app->has_render_context())
				//	{
				//		on_post_draw(app->get_render_context());
				//	}
		}
	}

	void Platform::Terminate(ExitCode code)
	{
		if (code == ExitCode::NoSample)
		{
			LOGI("");
			LOGI("No sample was requested or the selected sample does not exist");
			LOGI("");
			LOGI("To run a specific sample use the \"sample\" argument, e.g.");
			LOGI("");
			LOGI("\tvulkan_samples sample hello_triangle");
			LOGI("");
			LOGI("To get a list of available samples, use the \"samples\" argument")
				LOGI("To get a list of available command line options, use the \"-h\" or \"--help\" argument");
			LOGI("");
		}

		if (active_app)
		{
			std::string id = active_app->GetName();
			on_app_close(id);
			active_app->Finish();
		}

		active_app.reset();
		window.reset();


		on_platform_close();
		spdlog::drop_all();

#ifdef HT_PLATFORM_WINDOWS
		// Halt on all unsuccessful exit codes unless ForceClose is in use
		/*if (code != ExitCode::Success && !using_plugin<::plugins::ForceClose>())
		{
			std::cout << "Press return to continue";
			std::cin.get();
		}*/
#endif
	}

	void Platform::Close()
	{
		if (window)
		{
			window->Close();
		}

		// Fallback incase a window is not yet in use
		close_requested = true;
	}

	/*void Platform::force_simulation_fps(float fps)
	{
		fixed_simulation_fps = true;
		simulation_frame_time = 1 / fps;
	}

	void Platform::disable_input_processing()
	{
		process_input_events = false;
	}*/

	void Platform::SetFocus(bool _focused)
	{
		focused = _focused;
	}

	void Platform::SetApplicationInfo(const AppCreateInfo* app)
	{
		requested_app = app;
	}

	void Platform::SetWindowProperties(const Window::OptionalProperties& properties)
	{
		window_properties.title = properties.title.has_value() ? properties.title.value() : window_properties.title;
		window_properties.mode = properties.mode.has_value() ? properties.mode.value() : window_properties.mode;
		window_properties.resizable = properties.resizable.has_value() ? properties.resizable.value() : window_properties.resizable;
		window_properties.vsync = properties.vsync.has_value() ? properties.vsync.value() : window_properties.vsync;
		window_properties.extent.width = properties.extent.width.has_value() ? properties.extent.width.value() : window_properties.extent.width;
		window_properties.extent.height = properties.extent.height.has_value() ? properties.extent.height.value() : window_properties.extent.height;
	}

	const std::string& Platform::GetExternalStorageDirectory()
	{
		return external_storage_directory;
	}

	const std::string& Platform::GetTempDirectory()
	{
		return temp_directory;
	}

	Application& Platform::GetApp()
	{
		assert(active_app && "Application is not valid");
		return *active_app;
	}

	Application& Platform::GetApp() const
	{
		assert(active_app && "Application is not valid");
		return *active_app;
	}

	Window& Platform::GetWindow()
	{
		return *window;
	}

	void Platform::SetExternalStorageDirectory(const std::string& dir)
	{
		external_storage_directory = dir;
	}

	std::vector<spdlog::sink_ptr> Platform::GetPlatformSinks()
	{
		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		return sinks;
	}

	bool Platform::NeedsToLoadApp()
	{
		return requested_app != nullptr;
	}

	bool Platform::StartApp()
	{
		auto* requested_app_info = requested_app;
		// Reset early incase error in preparation stage
		requested_app = nullptr;

		if (active_app)
		{
			auto execution_time = timer.Stop();
			LOGI("Closing App (Runtime: {:.1f})", execution_time);

			auto app_id = active_app->GetName();

			active_app->Finish();
		}

		active_app = requested_app_info->create();

		active_app->SetName(requested_app_info->id);

		if (!active_app)
		{
			LOGE("Failed to create a valid vulkan app.");
			return false;
		}

		if (!active_app->Prepare({ false, window.get() }))
		{
			LOGE("Failed to prepare vulkan app.");
			return false;
		}

		on_app_start(requested_app_info->id);

		return true;
	}

	void Platform::InputEvent(const HT::InputEvent& input_event)
	{
		if (process_input_events && active_app)
		{
			active_app->InputEvent(input_event);
		}

		if (input_event.GetSource() == EventSource::Keyboard)
		{
			const auto& key_event = static_cast<const KeyInputEvent&>(input_event);

			if (key_event.GetCode() == KeyCode::Back ||
				key_event.GetCode() == KeyCode::Escape)
			{
				Close();
			}
		}
	}

	void Platform::Resize(uint32_t width, uint32_t height)
	{
		auto extent = Window::Extent{ std::max<uint32_t>(width, MIN_WINDOW_WIDTH), std::max<uint32_t>(height, MIN_WINDOW_HEIGHT) };
		if ((window) && (width > 0) && (height > 0))
		{
			auto actual_extent = window->Resize(extent);

			if (active_app)
			{
				active_app->Resize(actual_extent.width, actual_extent.height);
			}
		}
	}

//#define HOOK(enum, func)                \
//	static auto res = hooks.find(enum); \
//	if (res != hooks.end())             \
//	{                                   \
//		for (auto plugin : res->second) \
//		{                               \
//			plugin->func;               \
//		}                               \
//	}

	//void Platform::on_post_draw(RenderContext& context)
	//{
	//	HOOK(Hook::PostDraw, on_post_draw(context));
	//}

	void Platform::on_app_error(const std::string& app_id)
	{
		LOGE("On App Error");
		//HOOK(Hook::OnAppError, on_app_error(app_id));
	}

	void Platform::on_update(float delta_time)
	{
		//HOOK(Hook::OnUpdate, on_update(delta_time));
	}

	void Platform::on_app_start(const std::string& app_id)
	{
		LOGI("On App Start");
		//HOOK(Hook::OnAppStart, on_app_start(app_id));
	}

	void Platform::on_app_close(const std::string& app_id)
	{
		LOGI("On App Close");
		//HOOK(Hook::OnAppClose, on_app_close(app_id));
	}

	void Platform::on_platform_close()
	{
		LOGI("On Platform Close");
		//HOOK(Hook::OnPlatformClose, on_platform_close());
	}

	//void Platform::on_update_ui_overlay(vkb::Drawer& drawer)
	//{
	//	HOOK(Hook::OnUpdateUi, on_update_ui_overlay(drawer));
	//}

#undef HOOK

}       
