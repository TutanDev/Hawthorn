/* Copyright (c) 2018-2023, Arm Limited and Contributors
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

#include "Window.h"

#include "core/platform/Platform.h"

namespace HT
{
	Window::Window(const Properties& properties) :
		properties{ properties }
	{
	}

	void Window::ProcessEvents()
	{
	}

	Window::Extent Window::Resize(const Extent& new_extent)
	{
		if (properties.resizable)
		{
			properties.extent.width = new_extent.width;
			properties.extent.height = new_extent.height;
		}

		return properties.extent;
	}

	const Window::Extent& Window::GetExtent() const
	{
		return properties.extent;
	}

	float Window::GetContentScaleFactor() const
	{
		return 1.0f;
	}

	Window::Mode Window::GetWindowMode() const
	{
		return properties.mode;
	}
} 
