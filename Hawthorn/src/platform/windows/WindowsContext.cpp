
#include "WindowsContext.h"

#include <Windows.h>
#include <cassert>
#include <stdexcept>

namespace HT
{

	inline const std::string get_temp_path_from_environment()
	{
		std::string temp_path = "temp/";

		TCHAR temp_buffer[MAX_PATH];
		DWORD temp_path_ret = GetTempPath(MAX_PATH, temp_buffer);
		if (temp_path_ret > MAX_PATH || temp_path_ret == 0)
		{
			temp_path = "temp/";
		}
		else
		{
			temp_path = "temp//";
		}

		return temp_path;
	}

	/// @brief Converts wstring to string using Windows specific function
	/// @param wstr Wide string to convert
	/// @return A converted utf8 string
	inline std::string wstr_to_str(const std::wstring& wstr)
	{
		if (wstr.empty())
		{
			return {};
		}

		auto wstr_len = static_cast<int>(wstr.size());
		auto str_len = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], wstr_len, NULL, 0, NULL, NULL);

		std::string str(str_len, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], wstr_len, &str[0], str_len, NULL, NULL);

		return str;
	}

	inline std::vector<std::string> get_args()
	{
		LPWSTR* argv;
		int     argc;

		argv = CommandLineToArgvW(GetCommandLineW(), &argc);

		// Ignore the first argument containing the application full path
		std::vector<std::wstring> arg_strings(argv + 1, argv + argc);
		std::vector<std::string>  args;

		for (auto& arg : arg_strings)
		{
			args.push_back(wstr_to_str(arg));
		}

		return args;
	}

	WindowsPlatformContext::WindowsPlatformContext(/*HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow*/) :
		PlatformContext{}
	{
		_external_storage_directory = "";
		_temp_directory = get_temp_path_from_environment();
		_arguments = get_args();

		// Attempt to attach to the parent process console if it exists
		if (!AttachConsole(ATTACH_PARENT_PROCESS))
		{
			// No parent console, allocate a new one for this process
			if (!AllocConsole())
			{
				//throw std::runtime_error{ "AllocConsole error" };
			}
		}

		FILE* fp;
		freopen_s(&fp, "conin$", "r", stdin);
		freopen_s(&fp, "conout$", "w", stdout);
		freopen_s(&fp, "conout$", "w", stderr);
	}
}