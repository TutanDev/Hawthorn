#pragma once

#include "core/types/Optional.h"
//#include "common/vk_common.h"
//#include "core/instance.h"

#include <cstdint>
#include <string>
#include <vector>

namespace HT
{
	/**
	 * @brief An interface class, declaring the behaviour of a Window
	 */
	class Window
	{
	public:
		struct Extent
		{
			uint32_t width;
			uint32_t height;
		};

		struct OptionalExtent
		{
			Optional<uint32_t> width;
			Optional<uint32_t> height;
		};

		enum class Mode
		{
			Headless,
			Fullscreen,
			FullscreenBorderless,
			FullscreenStretch,
			Default
		};

		enum class Vsync
		{
			OFF,
			ON,
			Default
		};

		struct OptionalProperties
		{
			Optional<std::string> title;
			Optional<Mode>        mode;
			Optional<bool>        resizable;
			Optional<Vsync>       vsync;
			OptionalExtent        extent;
		};

		struct Properties
		{
			std::string title = "";
			Mode        mode = Mode::Default;
			bool        resizable = true;
			Vsync       vsync = Vsync::Default;
			Extent      extent = { 1280, 720 };
		};

		/**
		 * @brief Constructs a Window
		 * @param properties The preferred configuration of the window
		 */
		Window(const Properties& properties);

		virtual ~Window() = default;

		/**
		 * @brief Gets a handle from the platform's Vulkan surface
		 * @param instance A Vulkan instance
		 * @returns A VkSurfaceKHR handle, for use by the application
		 */
		//virtual VkSurfaceKHR create_surface(Instance& instance) = 0;

		/**
		 * @brief Gets a handle from the platform's Vulkan surface
		 * @param instance A Vulkan instance
		 * @param physical_device A Vulkan PhysicalDevice
		 * @returns A VkSurfaceKHR handle, for use by the application
		 */
		//virtual VkSurfaceKHR create_surface(VkInstance instance, VkPhysicalDevice physical_device) = 0;

		/**
		 * @brief Checks if the window should be closed
		 */
		virtual bool ShouldClose() = 0;

		/**
		 * @brief Handles the processing of all underlying window events
		 */
		virtual void ProcessEvents();

		/**
		 * @brief Requests to close the window
		 */
		virtual void Close() = 0;

		/**
		 * @return The dot-per-inch scale factor
		 */
		virtual float GetDpiFactor() const = 0;

		/**
		 * @return The scale factor for systems with heterogeneous window and pixel coordinates
		 */
		virtual float GetContentScaleFactor() const;

		/**
		 * @brief Attempt to resize the window - not guaranteed to change
		 *
		 * @param extent The preferred window extent
		 * @return Extent The new window extent
		 */
		Extent Resize(const Extent& extent);

		/**
		 * @brief Get the display present info for the window if needed
		 *
		 * @param info Filled in when the method returns true
		 * @param src_width The width of the surface being presented
		 * @param src_height The height of the surface being presented
		 * @return true if the present info was filled in and should be used
		 * @return false if the extra present info should not be used. info is left untouched.
		 */
		//virtual bool get_display_present_info(VkDisplayPresentInfoKHR* info,
		//	uint32_t src_width, uint32_t src_height) const;

		virtual std::vector<const char*> GetRequiredSurfaceExtensions() const = 0;

		const Extent& GetExtent() const;

		Mode GetWindowMode() const;

		inline const Properties& get_properties() const
		{
			return properties;
		}

	protected:
		Properties properties;
	};
}       
