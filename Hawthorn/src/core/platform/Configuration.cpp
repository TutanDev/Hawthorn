#include "Configuration.h"

namespace HT
{
	BoolSetting::BoolSetting(bool& handle, bool value) :
		handle{ handle },
		value{ value }
	{
	}

	void BoolSetting::Set()
	{
		handle = value;
	}

	std::type_index BoolSetting::GetType()
	{
		return typeid(BoolSetting);
	}

	IntSetting::IntSetting(int& handle, int value) :
		handle{ handle },
		value{ value }
	{
	}

	void IntSetting::Set()
	{
		handle = value;
	}

	std::type_index IntSetting::GetType()
	{
		return typeid(IntSetting);
	}

	EmptySetting::EmptySetting()
	{
	}

	void EmptySetting::Set()
	{
	}

	std::type_index EmptySetting::GetType()
	{
		return typeid(EmptySetting);
	}

	void Configuration::Set()
	{
		for (auto pair : current_configuration->second)
		{
			for (auto setting : pair.second)
			{
				setting->Set();
			}
		}
	}

	bool Configuration::Next()
	{
		if (configs.size() == 0)
		{
			return false;
		}

		current_configuration++;

		if (current_configuration == configs.end())
		{
			return false;
		}

		return true;
	}

	void Configuration::Reset()
	{
		current_configuration = configs.begin();
	}

	void Configuration::InsertSetting(uint32_t config_index, std::unique_ptr<Setting> setting)
	{
		settings.push_back(std::move(setting));
		configs[config_index][settings.back()->GetType()].push_back(settings.back().get());
	}

}        // namespace vkb
