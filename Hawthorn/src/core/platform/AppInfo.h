#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Application.h"

 /*
  *
  *	Vulkan Samples currently has two types of apps, Samples and Tests. These apps work from the same interface AppInfo.
  *	Samples and Tests are categorised into namespaces samples and tests respectively. Each name space has a method to retrieve
  *  the AppInfo interface version of the app (tests::get_apps, samples::get_apps).
  *
  */

namespace HT
{
	using CreateFunc = std::function<std::unique_ptr<Application>()>;

	/*
	 *  Apps - Used by Vulkan Samples to load a vkb::Applicaiton with the creation function (CreateFunc create).
	 */

	class AppInfo
	{
	public:
		AppInfo(const std::string& id, const CreateFunc& create) :
			id(id), create(create)
		{}

		std::string id;
		CreateFunc  create;
	};

	AppInfo* GetApp(const std::string& id);

	/**
	 * @brief Get all apps
	 *
	 * @return const std::vector<AppInfo *> A list of all apps
	 */
	std::vector<AppInfo*> GetApps();
}       