#include "Drawer.h"

namespace HT
{

	void Drawer::Clear()
	{
		dirty = false;
	}

	bool Drawer::IsDirty()
	{
		return dirty;
	}

	void Drawer::SetDirty(bool dirty)
	{
		this->dirty = dirty;
	}

	bool Drawer::Header(const char* caption)
	{
		return ImGui::CollapsingHeader(caption, ImGuiTreeNodeFlags_DefaultOpen);
	}

	bool Drawer::CheckBox(const char* caption, bool* value)
	{
		bool res = ImGui::Checkbox(caption, value);
		if (res)
		{
			dirty = true;
		};
		return res;
	}

	bool Drawer::CheckBox(const char* caption, int32_t* value)
	{
		bool val = (*value == 1);
		bool res = ImGui::Checkbox(caption, &val);
		*value = val;
		if (res)
		{
			dirty = true;
		};
		return res;
	}

	bool Drawer::RadioButton(const char* caption, int32_t* selectedOption, const int32_t elementOption)
	{
		bool res = ImGui::RadioButton(caption, selectedOption, elementOption);
		if (res)
			dirty = true;

		return res;
	}

	bool Drawer::InputFloat(const char* caption, float* value, float step, const char* precision)
	{
		bool res = ImGui::InputFloat(caption, value, step, step * 10.0f, precision);
		if (res)
		{
			dirty = true;
		};
		return res;
	}

	bool Drawer::SliderFloat(const char* caption, float* value, float min, float max)
	{
		bool res = ImGui::SliderFloat(caption, value, min, max);
		if (res)
		{
			dirty = true;
		};
		return res;
	}

	bool Drawer::SliderInt(const char* caption, int32_t* value, int32_t min, int32_t max)
	{
		bool res = ImGui::SliderInt(caption, value, min, max);
		if (res)
		{
			dirty = true;
		};
		return res;
	}

	bool Drawer::ComboBox(const char* caption, int32_t* itemindex, std::vector<std::string> items)
	{
		if (items.empty())
		{
			return false;
		}
		std::vector<const char*> charitems;
		charitems.reserve(items.size());
		for (size_t i = 0; i < items.size(); i++)
		{
			charitems.push_back(items[i].c_str());
		}
		uint32_t itemCount = static_cast<uint32_t>(charitems.size());
		bool     res = ImGui::Combo(caption, itemindex, &charitems[0], itemCount, itemCount);
		if (res)
		{
			dirty = true;
		};
		return res;
	}

	bool Drawer::Button(const char* caption)
	{
		bool res = ImGui::Button(caption);
		if (res)
		{
			dirty = true;
		};
		return res;
	}

	void Drawer::Text(const char* formatstr, ...)
	{
		va_list args;
		va_start(args, formatstr);
		ImGui::TextV(formatstr, args);
		va_end(args);
	}

	template <>
	bool Drawer::color_op_impl<Drawer::ColorOp::Edit, 3>(const char* caption, float* colors, ImGuiColorEditFlags flags)
	{
		return ImGui::ColorEdit3(caption, colors, flags);
	}

	template <>
	bool Drawer::color_op_impl<Drawer::ColorOp::Edit, 4>(const char* caption, float* colors, ImGuiColorEditFlags flags)
	{
		return ImGui::ColorEdit4(caption, colors, flags);
	}

	template <>
	bool Drawer::color_op_impl<Drawer::ColorOp::Pick, 3>(const char* caption, float* colors, ImGuiColorEditFlags flags)
	{
		return ImGui::ColorPicker3(caption, colors, flags);
	}

	template <>
	bool Drawer::color_op_impl<Drawer::ColorOp::Pick, 4>(const char* caption, float* colors, ImGuiColorEditFlags flags)
	{
		return ImGui::ColorPicker4(caption, colors, flags);
	}

}
