#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Context.h"

#include "AppInfo.h"
//#include "common/optional.h"
//#include "common/utils.h"
//#include "common/vk_common.h"
//#include "filesystem/legacy.h"
#include "Application.h"
//#include "platform/parser.h"
//#include "platform/plugins/plugin.h"
#include "core/windowing/Window.h"
//#include "rendering/render_context.h"

#include <spdlog/spdlog.h>

#if defined(VK_USE_PLATFORM_XLIB_KHR)
#	undef Success
#endif

namespace HT
{
	enum class ExitCode
	{
		Success = 0, /* App executed as expected */
		NoSample,    /* App should show help how to run a sample */
		Help,        /* App should show help */
		Close,       /* App has been requested to close at initialization */
		FatalError   /* App encountered an unexpected error */
	};

	class Platform
	{
	public:
		Platform(const PlatformContext& context);

		virtual ~Platform() = default;

		/**
		 * @brief Initialize the platform
		 * @param plugins plugins available to the platform
		 * @return An exit code representing the outcome of initialization
		 */
		//virtual ExitCode initialize(const std::vector<Plugin*>& plugins);
		virtual ExitCode Initialize();

		/**
		 * @brief Handles the main loop of the platform
		 * This should be overriden if a platform requires a specific main loop setup.
		 * @return An exit code representing the outcome of the loop
		 */
		ExitCode MainLoop();
		ExitCode MainLoopFrame();

		/**
		 * @brief Runs the application for one frame
		 */
		void Update();

		/**
		 * @brief Terminates the platform and the application
		 * @param code Determines how the platform should exit
		 */
		virtual void Terminate(ExitCode code);

		/**
		 * @brief Requests to close the platform at the next available point
		 */
		virtual void Close();

		/**
		 * @brief Returns the working directory of the application set by the platform
		 * @returns The path to the working directory
		 */
		static const std::string& GetExternalStorageDirectory();

		/**
		 * @brief Returns the suitable directory for temporary files from the environment variables set in the system
		 * @returns The path to the temp folder on the system
		 */
		static const std::string& GetTempDirectory();

		virtual void Resize(uint32_t width, uint32_t height);

		virtual void InputEvent(const InputEvent& input_event);

		Window& GetWindow();

		Application& GetApp() const;

		Application& GetApp();

		static void SetExternalStorageDirectory(const std::string& dir);

		//template <class T>
		//T* get_plugin() const;

		//template <class T>
		//bool using_plugin() const;

		void SetFocus(bool focused);

		//void request_application(const apps::AppInfo* app);

		//bool app_requested();

		bool StartApp(const AppInfo* app);

		//void force_simulation_fps(float fps);

		//void disable_input_processing();

		void SetWindowProperties(const Window::OptionalProperties& properties);

		//void on_post_draw(RenderContext& context);

		static const uint32_t MIN_WINDOW_WIDTH;
		static const uint32_t MIN_WINDOW_HEIGHT;

	protected:
		//std::unique_ptr<CommandParser> parser;

		//std::vector<Plugin*> active_plugins;

		//std::unordered_map<Hook, std::vector<Plugin*>> hooks;

		std::unique_ptr<Window> window{ nullptr };

		std::unique_ptr<Application> active_app{ nullptr };

		virtual std::vector<spdlog::sink_ptr> GetPlatformSinks();

		/**
		 * @brief Handles the creation of the window
		 *
		 * @param properties Preferred window configuration
		 */
		virtual void createWindow(const Window::Properties& properties) = 0;

		void on_update(float delta_time);
		void on_app_error(const std::string& app_id);
		void on_app_start(const std::string& app_id);
		void on_app_close(const std::string& app_id);
		void on_platform_close();
		//void on_update_ui_overlay(vkb::Drawer& drawer);

		Window::Properties window_properties;              /* Source of truth for window state */
		bool               fixed_simulation_fps{ false };    /* Delta time should be fixed with a fabricated value */
		float              simulation_frame_time = 0.016f; /* A fabricated delta time */
		bool               process_input_events{ true };     /* App should continue processing input events */
		bool               focused{ true };                  /* App is currently in focus at an operating system level */
		bool               close_requested{ false };         /* Close requested */

	private:
		//Timer timer;

		//const apps::AppInfo* requested_app{ nullptr };

		//std::vector<Plugin*> plugins;

		std::vector<std::string> arguments;

		// static so can be references from vkb::fs
		static std::string external_storage_directory;

		// static so can be references from vkb::fs
		static std::string temp_directory;
	};

	//template <class T>
	//bool Platform::using_plugin() const
	//{
	//	return !plugins::with_tags<T>(active_plugins).empty();
	//}

	//template <class T>
	//T* Platform::get_plugin() const
	//{
	//	assert(using_plugin<T>() && "Plugin is not enabled but was requested");
	//	const auto plugins = plugins::with_tags<T>(active_plugins);
	//	return dynamic_cast<T*>(plugins[0]);
	//}
}      
