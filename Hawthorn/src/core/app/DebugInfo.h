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
#include <utility>
#include <vector>
#include <memory>

//#include "common/error.h"

#include "core/util/glmCommon.h"

#include "core/util/Helpers.h"

namespace HT
{
	namespace Fields
	{
		/**
		 * @brief Base Field Interface class
		 */
		struct Base
		{
			std::string label;

			Base(const std::string& label) :
				label{ label }
			{}

			virtual ~Base() = default;

			virtual const std::string to_string() = 0;
		};

		/**
		 * @brief Static Field Implementation
		 *
		 * To be used for values that do not change often.
		 */
		template <typename T>
		struct Static : public Base
		{
			T value;

			Static(const std::string& label, const T& value) :
				Base(label),
				value{ value }
			{}

			virtual ~Static() = default;

			const std::string to_string() override
			{
				return HT::to_string(value);
			}
		};

		/**
		 * @brief Dynamic Field Implementation
		 *
		 * To be used for values that change frequently.
		 */
		template <typename T>
		struct Dynamic : public Base
		{
			T& value;

			Dynamic(const std::string& label, T& value) :
				Base(label),
				value{ value }
			{}

			virtual ~Dynamic() = default;

			const std::string to_string() override
			{
				return HT::to_string(value);
			}
		};

		/**
		 * @brief Vector Field Implementation
		 *
		 * To be used for values that have an X, Y and Z value.
		 */
		template <typename T>
		struct Vector final : public Static<T>
		{
			T x, y, z;

			Vector(const std::string& label, const glm::vec3& vec) :
				Vector(label, vec.x, vec.y, vec.z)
			{}
			Vector(const std::string& label, T x, T y, T z) :
				Static<T>(label, x),
				x{ x },
				y{ y },
				z{ z }
			{}

			virtual ~Vector() = default;

			const std::string to_string() override
			{
				return  "x: " + HT::to_string(x) + " " +
						"y: " + HT::to_string(y) + " " +
						"z: " + HT::to_string(z);
			}
		};

		/**
		 * @brief MinMax Field Implementation
		 *
		 * To be used for numbers that change a lot, keeping track of the high/low values.
		 */
		template <typename T>
		struct MinMax final : public Dynamic<T>
		{
			T min, max;

			MinMax(const std::string& label, T& value) :
				Dynamic<T>(label, value),
				min{ value },
				max{ value }
			{
				static_assert(std::is_arithmetic<T>::value, "MinMax must be templated to a numeric type.");
			}

			virtual ~MinMax() = default;

			const std::string to_string() override
			{
				if (Dynamic<T>::value > max)
				{
					max = Dynamic<T>::value;
				}
				if (Dynamic<T>::value < min)
				{
					min = Dynamic<T>::value;
				}
				if (min == 0)
				{
					min = Dynamic<T>::value;
				}

				return "current: " + HT::to_string(Dynamic<T>::value) + " min: " + HT::to_string(min) + " max: " + HT::to_string(max);
			}
		};
	}        // namespace field

	/**
	 * @brief Manages the debug information
	 */
	class DebugInfo
	{
	public:
		const std::vector<std::unique_ptr<Fields::Base>>& GetFields() const;

		/**
		 * @brief   Calculates the field label with the most amount of characters
		 * @returns The length of the longest label
		 */
		float GetLongestLabel() const;

		/**
		 * @brief Constructs and inserts a new field of type C<T>
		 *
		 * Replaces the field if it is of type static.
		 */
		template <template <typename> class C, typename T, typename... A>
		void Insert(const std::string& label, A &&...args)
		{
			static_assert(std::is_base_of<Fields::Base, C<T>>::value, "C is not a type of field::Base.");

			for (auto& field : fields)
			{
				if (field->label == label)
				{
					if (dynamic_cast<typename Fields::Static<T> *>(field.get()))
					{
						field = std::make_unique<C<T>>(label, args...);
					}
					return;
				}
			}

			auto field = std::make_unique<C<T>>(label, std::forward<A>(args)...);
			fields.push_back(std::move(field));
		}

	private:
		std::vector<std::unique_ptr<Fields::Base>> fields;
	};
}        // namespace vkb
