#include "core/file_system/Filesystem.h"

#include <filesystem>

namespace HT
{
	namespace FS
	{
		class StdFileSystem final : public FileSystem
		{
		public:
			StdFileSystem(stdPath external_storage_directory = std::filesystem::current_path(), stdPath temp_directory = std::filesystem::temp_directory_path()) :
				_external_storage_directory(std::move(external_storage_directory)),
				_temp_directory(std::move(temp_directory))
			{}

			virtual ~StdFileSystem() = default;

			FileStat stat_file(const stdPath& path) override;

			bool is_file(const stdPath& path) override;

			bool is_directory(const stdPath& path) override;

			bool exists(const stdPath& path) override;

			bool create_directory(const stdPath& path) override;

			std::vector<uint8_t> read_chunk(const stdPath& path, size_t offset, size_t count) override;

			void write_file(const stdPath& path, const std::vector<uint8_t>& data) override;

			virtual void remove(const stdPath& path) override;

			const stdPath& external_storage_directory() const override;

			const stdPath& temp_directory() const override;

		private:
			stdPath _external_storage_directory;
			stdPath _temp_directory;
		};
	}        // FS
}        // HT