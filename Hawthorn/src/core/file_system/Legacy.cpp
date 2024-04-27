#include "Legacy.h"

//#include "core/util/error.hpp"

//VKBP_DISABLE_WARNINGS()
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include <stb_image_write.h>
//VKBP_ENABLE_WARNINGS()

#include "FileSystem.h"

namespace HT
{
	namespace FS
	{
		void create_Path(const std::string& root, const std::string& Path);

		namespace Path
		{
			const std::unordered_map<Type, std::string> relative_Paths = 
			{
				{Type::Assets, "assets/"},
				{Type::Shaders, "shaders/"},
				{Type::Storage, "output/"},
				{Type::Screenshots, "output/images/"},
				{Type::Logs, "output/logs/"},
			};

			const std::string get(const Type type, const std::string& file)
			{
				assert(relative_Paths.size() == Type::TotalRelativePathTypes && "Not all Paths are defined in filesystem, please check that each enum is specified");

				// Check for special cases first
				if (type == Type::Temp)
				{
					return HT::FS::get()->temp_directory().string();
				}

				// Check for relative Paths
				auto it = relative_Paths.find(type);

				if (relative_Paths.size() < Type::TotalRelativePathTypes)
				{
					throw std::runtime_error("Platform hasn't initialized the Paths correctly");
				}
				else if (it == relative_Paths.end())
				{
					throw std::runtime_error("Path enum doesn't exist, or wasn't specified in the Path map");
				}
				else if (it->second.empty())
				{
					throw std::runtime_error("Path was found, but it is empty");
				}

				auto fs = HT::FS::get();
				auto Path = fs->external_storage_directory() / it->second;

				if (!is_directory(Path))
				{
					create_Path(fs->external_storage_directory().string(), it->second);
				}

				auto full_Path = Path / file;
				return full_Path.string();
			}
		}        // namespace Path

		bool is_directory(const std::string& Path)
		{
			return HT::FS::get()->is_directory(Path);
		}

		bool is_file(const std::string& filename)
		{
			return HT::FS::get()->is_file(filename);
		}

		void create_directory(const std::string& Path)
		{
			HT::FS::get()->create_directory(Path);
		}

		void create_Path(const std::string& root, const std::string& Path)
		{
			for (auto it = Path.begin(); it != Path.end(); ++it)
			{
				it = std::find(it, Path.end(), '/');
				create_directory(root + std::string(Path.begin(), it));
			}
		}

		std::vector<uint8_t> read_asset(const std::string& filename)
		{
			return HT::FS::get()->read_file_binary(Path::get(Path::Type::Assets) + filename);
		}

		std::string read_shader(const std::string& filename)
		{
			return HT::FS::get()->read_file_string(Path::get(Path::Type::Shaders) + filename);
		}

		std::vector<uint8_t> read_shader_binary(const std::string& filename)
		{
			return HT::FS::get()->read_file_binary(Path::get(Path::Type::Shaders) + filename);
		}

		std::vector<uint8_t> read_temp(const std::string& filename)
		{
			return HT::FS::get()->read_file_binary(Path::get(Path::Type::Temp) + filename);
		}

		void write_temp(const std::vector<uint8_t>& data, const std::string& filename)
		{
			HT::FS::get()->write_file(Path::get(Path::Type::Temp) + filename, data);
		}

		void write_image(const uint8_t* data, const std::string& filename, const uint32_t width, const uint32_t height, const uint32_t components, const uint32_t row_stride)
		{
			//stbi_write_png((Path::get(Path::Type::Screenshots) + filename + ".png").c_str(), width, height, components, data, row_stride);
		}

	}        // FS
}        // HT
