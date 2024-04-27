#include "stdFileSystem.h"


#include <core/util/Logger.h>

#include <filesystem>
#include <fstream>

namespace HT
{
	namespace FS
	{
		FileStat StdFileSystem::stat_file(const stdPath& path)
		{
			std::error_code ec;

			auto fs_stat = std::filesystem::status(path, ec);
			if (ec)
			{
				return FileStat{
					false,
					false,
					0,
				};
			}

			auto size = std::filesystem::file_size(path, ec);
			if (ec)
			{
				size = 0;
			}

			return FileStat{
				fs_stat.type() == std::filesystem::file_type::regular,
				fs_stat.type() == std::filesystem::file_type::directory,
				size,
			};
		}

		bool StdFileSystem::is_file(const stdPath& path)
		{
			auto stat = stat_file(path);
			return stat.is_file;
		}

		bool StdFileSystem::is_directory(const stdPath& path)
		{
			auto stat = stat_file(path);
			return stat.is_directory;
		}

		bool StdFileSystem::exists(const stdPath& path)
		{
			auto stat = stat_file(path);
			return stat.is_file || stat.is_directory;
		}

		bool StdFileSystem::create_directory(const stdPath& path)
		{
			std::error_code ec;

			std::filesystem::create_directory(path, ec);

			if (ec)
			{
				throw std::runtime_error("Failed to create directory");
			}

			return !ec;
		}

		std::vector<uint8_t> StdFileSystem::read_chunk(const stdPath& path, size_t offset, size_t count)
		{
			std::ifstream file{ path, std::ios::binary | std::ios::ate };

			if (!file.is_open())
			{
				throw std::runtime_error("Failed to open file for reading");
			}

			auto size = stat_file(path).size;

			if (offset + count > size)
			{
				return {};
			}

			// read file contents
			file.seekg(offset, std::ios::beg);
			std::vector<uint8_t> data(count);
			file.read(reinterpret_cast<char*>(data.data()), count);

			return data;
		}

		void StdFileSystem::write_file(const stdPath& path, const std::vector<uint8_t>& data)
		{
			// create directory if it doesn't exist
			auto parent = path.parent_path();
			if (!std::filesystem::exists(parent))
			{
				create_directory(parent);
			}

			std::ofstream file{ path, std::ios::binary | std::ios::trunc };

			if (!file.is_open())
			{
				throw std::runtime_error("Failed to open file for writing");
			}

			file.write(reinterpret_cast<const char*>(data.data()), data.size());
		}

		void StdFileSystem::remove(const stdPath& path)
		{
			std::error_code ec;

			std::filesystem::remove(path, ec);

			if (ec)
			{
				throw std::runtime_error("Failed to remove file");
			}
		}

		const stdPath& StdFileSystem::external_storage_directory() const
		{
			return _external_storage_directory;
		}

		const stdPath& StdFileSystem::temp_directory() const
		{
			return _temp_directory;
		}

	}        
}