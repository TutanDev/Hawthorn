#include "DebugInfo.h"

namespace HT
{
	const std::vector<std::unique_ptr<Fields::Base>>& DebugInfo::GetFields() const
	{
		return fields;
	}

	float DebugInfo::GetLongestLabel() const
	{
		float column_width = 0.0f;
		for (auto& field : fields)
		{
			const std::string& label = field->label;

			if (label.size() > column_width)
			{
				column_width = static_cast<float>(label.size());
			}
		}
		return column_width;
	}
}
