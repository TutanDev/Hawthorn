#pragma once

#include <string>
#include <iostream>

namespace HT
{
	/**
	 * @brief Helper function to convert a data type
	 *        to string using output stream operator.
	 * @param value The object to be converted to string
	 * @return String version of the given object
	 */
	template <class T>
	inline std::string to_string(const T& value)
	{
		/*std::stringstream ss;
		ss << std::fixed << value;
		return ss.str();*/
		return "to_string not implemented for this type";
	}
}