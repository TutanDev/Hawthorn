#include "Application.h"

#include "core/util/Logger.h"
#include "core/windowing/Window.h"

namespace HT
{
	Application::Application() :
		name{ "Sample Name" }
	{
	}

	bool Application::Prepare(const ApplicationOptions& options)
	{
		assert(options.window != nullptr && "Window must be valid");

		auto& _debug_info = GetDebugInfo();
		_debug_info.Insert<Fields::MinMax, float>("fps", fps);
		_debug_info.Insert<Fields::MinMax, float>("frame_time", frame_time);

		window = options.window;

		return true;
	}

	void Application::Finish()
	{
	}

	bool Application::Resize(const uint32_t /*width*/, const uint32_t /*height*/)
	{
		return true;
	}

	void Application::InputEvent(const HT::InputEvent& input_event)
	{
	}

	Drawer* Application::GetDrawer()
	{
		return nullptr;
	}

	void Application::Update(float delta_time)
	{
		fps = 1.0f / delta_time;
		frame_time = delta_time * 1000.0f;
	}

	void Application::UpdateOverlay(float delta_time, const std::function<void()>& additional_ui)
	{
	}

	const std::string& Application::GetName() const
	{
		return name;
	}

	void Application::SetName(const std::string& name_)
	{
		name = name_;
	}

	DebugInfo& Application::GetDebugInfo()
	{
		return debug_info;
	}

	/*void Application::change_shader(const vkb::ShaderSourceLanguage& shader_language)
	{
		LOGE("Not implemented by sample");
	}

	const std::map<ShaderSourceLanguage, std::vector<std::pair<VkShaderStageFlagBits, std::string>>>& Application::get_available_shaders() const
	{
		return available_shaders;
	}

	void Application::store_shaders(const vkb::ShaderSourceLanguage& shader_language, const std::vector<std::pair<VkShaderStageFlagBits, std::string>>& list_of_shaders)
	{
		available_shaders.insert({ shader_language, list_of_shaders });
	}*/

}   
