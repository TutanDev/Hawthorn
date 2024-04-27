#include "SandboxApp.h"

SandboxApp::~SandboxApp()
{
}

void SandboxApp::InputEvent(const HT::InputEvent& input_event)
{
}

void SandboxApp::UpdateOverlay(float delta_time, const std::function<void()>& additional_ui)
{
}

HT::Drawer* SandboxApp::GetDrawer()
{
	return nullptr;
}
