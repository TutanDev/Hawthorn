#pragma once

#include "core/app/Application.h"
#include "core/platform/EntryPoint.h"
#include "core/windowing/Window.h"
//#include "main.h"

#include <memory>

class SandboxApp : public HT::Application
{
public:
	SandboxApp() = default;
	~SandboxApp() override;

	virtual void InputEvent(const HT::InputEvent& input_event) override;
	virtual void UpdateOverlay(float delta_time, const std::function<void()>& additional_ui = []() {}) override;
	virtual HT::Drawer* GetDrawer() override;
};

std::unique_ptr<HT::Application> CreateSandboxApplication()
{
	return std::make_unique<SandboxApp>();
}


// TODO: This is a temporary solution to get the application info to the platform layer
HT::AppCreateInfo appInfo{ "Sandbox", CreateSandboxApplication };
void HT::GetAppInfo(HT::Platform& platform)
{
	HT::Window::OptionalProperties properties;
	properties.title = "Hawthorn - " + appInfo.id;

	platform.SetWindowProperties(properties);
	platform.SetApplicationInfo(&appInfo);
}