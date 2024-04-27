#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "core/platform/PlatformContext.h"
#include "core/util/Logger.h"

namespace HT
{
namespace FS
{
	struct FileStat
	{
		bool   is_file;
		bool   is_directory;
		size_t size;
	};

	using stdPath = std::filesystem::path;

	class FileSystem
	{
	public:
		FileSystem() = default;
		virtual ~FileSystem() = default;

		virtual FileStat             stat_file(const stdPath& path) = 0;
		virtual bool                 is_file(const stdPath& path) = 0;
		virtual bool                 is_directory(const stdPath& path) = 0;
		virtual bool                 exists(const stdPath& path) = 0;
		virtual bool                 create_directory(const stdPath& path) = 0;
		virtual std::vector<uint8_t> read_chunk(const stdPath& path, size_t offset, size_t count) = 0;
		virtual void                 write_file(const stdPath& path, const std::vector<uint8_t>& data) = 0;
		virtual void                 remove(const stdPath& path) = 0;

		virtual const stdPath& external_storage_directory() const = 0;
		virtual const stdPath& temp_directory() const = 0;

		void write_file(const stdPath& path, const std::string& data);

		// Read the entire file into a string
		std::string read_file_string(const stdPath& path);

		// Read the entire file into a vector of bytes
		std::vector<uint8_t> read_file_binary(const stdPath& path);
	};


	using FileSystemPtr = std::shared_ptr<FileSystem>;

	void init();

	// Initialize the filesystem with the given context
	void init_with_context(const PlatformContext& context);

	// Get the filesystem instance
	FileSystemPtr get();

	namespace Helpers
	{
		std::string filename(const std::string& path);
	}
} // FS
} // HT