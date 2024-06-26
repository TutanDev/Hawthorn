/* Copyright (c) 2019-2024, Arm Limited and Contributors
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 the "License";
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <string>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "DebugInfo.h"
#include "core/gui/Drawer.h"
#include "core/platform/Configuration.h"
#include "core/platform/InputEvents.h"




namespace HT
{
	class Window;
	class Application;

	using CreateFunc = std::function<std::unique_ptr<Application>()>;


	class AppCreateInfo
	{
	public:
		AppCreateInfo(const std::string& id, const CreateFunc& create) :
			id(id), create(create)
		{}

		std::string id;
		CreateFunc  create;
	};

	struct ApplicationOptions
	{
		bool    benchmark_enabled{ false };
		Window* window{ nullptr };
	};


	class Application
	{
	public:
		Application();

		virtual ~Application() = default;

		/**
		 * @brief Prepares the application for execution
		 */
		virtual bool Prepare(const ApplicationOptions& options);

		/**
		 * @brief Updates the application
		 * @param delta_time The time since the last update
		 */
		virtual void Update(float delta_time);

		/**
		 * @brief Main loop sample overlay events
		 * @param delta_time The time taken since the last frame
		 * @param additional_ui Function that implements an additional Gui
		 */
		virtual void UpdateOverlay(float delta_time, const std::function<void()>& additional_ui = []() {});

		/**
		 * @brief Handles cleaning up the application
		 */
		virtual void Finish();

		/**
		 * @brief Handles resizing of the window
		 * @param width New width of the window
		 * @param height New height of the window
		 */
		virtual bool Resize(const uint32_t width, const uint32_t height);

		/**
		 * @brief Handles input events of the window
		 * @param input_event The input event object
		 */
		virtual void InputEvent(const InputEvent& input_event);

		/**
		 * @brief Returns the drawer object for the sample
		 */
		virtual Drawer* GetDrawer();

		const std::string& GetName() const;

		void SetName(const std::string& name);

		DebugInfo& GetDebugInfo();

		inline bool ShouldClose() const
		{
			return requested_close;
		}

		// request the app to close
		// does not guarantee that the app will close immediately
		inline void Close()
		{
			requested_close = true;
		}

		/**
		 * @brief Indicates that the plugin wants to change the shader in the sample
		 * @param shader_language language the shader uses
		 */
		//virtual void ChangeShader(const vkb::ShaderSourceLanguage& shader_language);

		/**
		 * @brief Returns stored shaders by sample
		 */
		//const std::map<ShaderSourceLanguage, std::vector<std::pair<VkShaderStageFlagBits, std::string>>>& get_available_shaders() const;

	protected:
		/**
		 * @brief Stores a list of shaders for the active sample, used by plugins to dynamically change the shader
		 * @param shader_language The shader language for which the shader list will be provided
		 * @param list_of_shaders The shader list, where paths and shader types are provided
		 */
		//void store_shaders(const vkb::ShaderSourceLanguage& shader_language, const std::vector<std::pair<VkShaderStageFlagBits, std::string>>& list_of_shaders);

		float fps{ 0.0f };

		float frame_time{ 0.0f };        // In ms

		uint32_t frame_count{ 0 };

		uint32_t last_frame_count{ 0 };

		Window* window{ nullptr };

	private:
		std::string name{};

		/**
		 * @brief stores the names of the shaders the sample uses
		 */
		//std::map<ShaderSourceLanguage, std::vector<std::pair<VkShaderStageFlagBits, std::string>>> available_shaders;

		// The debug info of the app
		DebugInfo debug_info{};

		bool requested_close{ false };
	};

	// To be defined by the client
	void GetAppInfo(Platform& platform);
}   
