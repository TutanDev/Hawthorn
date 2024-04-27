#include "Filesystem.h"

#include "core/platform/PlatformContext.h"
//#include "core/util/error.hpp"

#include "stdFileSystem.h"

#include <memory>

namespace HT
{
	namespace FS
	{
		static FileSystemPtr fs = nullptr;

		void init()
		{
			fs = std::make_shared<StdFileSystem>();
		}

		void init_with_context(const PlatformContext& context)
		{
			fs = std::make_shared<StdFileSystem>(
				context.ExternalStorageDirectory(),
				context.TempDirectory());
		}

		FileSystemPtr get()
		{
			assert(fs && "Filesystem not initialized");
			return fs;
		}

		void FileSystem::write_file(const stdPath& path, const std::string& data)
		{
			write_file(path, std::vector<uint8_t>(data.begin(), data.end()));
		}

		std::string FileSystem::read_file_string(const stdPath& path)
		{
			auto bin = read_file_binary(path);
			return { bin.begin(), bin.end() };
		}

		std::vector<uint8_t> FileSystem::read_file_binary(const stdPath& path)
		{
			auto stat = stat_file(path);
			return read_chunk(path, 0, stat.size);
		}

	}        // FS
}        // HT