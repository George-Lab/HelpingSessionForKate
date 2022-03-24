#include <filesystem>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>

void file_type(const std::filesystem::path& p, std::filesystem::file_status s)
{
    //std::cout << p;
    switch(s.type())
    {
        case std::filesystem::file_type::none: std::cout << "type: `not-evaluated-yet` type"; break;
        case std::filesystem::file_type::not_found: std::cout << "type:  does not exist"; break;
        case std::filesystem::file_type::regular: std::cout << "type: regular file"; break;
        case std::filesystem::file_type::directory: std::cout << "type: directory"; break;
        case std::filesystem::file_type::symlink: std::cout << "type: symlink"; break;
        case std::filesystem::file_type::block: std::cout << "type: block device"; break;
        case std::filesystem::file_type::character: std::cout << "type: character device"; break;
        case std::filesystem::file_type::fifo: std::cout << "type: named IPC pipe"; break;
        case std::filesystem::file_type::socket: std::cout << "type: named IPC socket"; break;
        case std::filesystem::file_type::unknown: std::cout << "type: `unknown` type"; break;
        default: std::cout << "type: `implementation-defined` type"; break;
    }
}

void print_last_write_time(std::filesystem::file_time_type const& ftime) 
{
    std::time_t cftime = std::chrono::system_clock::to_time_t(
        std::chrono::file_clock::to_sys(ftime));
    std::cout << "File write time is " << std::asctime(std::localtime(&cftime));
};

void view_directory(const std::filesystem::path & path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (const auto & entry : std::filesystem::directory_iterator(path))
		{
			auto file_name = entry.path().filename().string();
			std::cout << file_name << " -- ";

            file_type(entry.path(), std::filesystem::status(entry.path()));
            std::cout <<", ";
            
            auto ftime = std::filesystem::last_write_time(entry.path());
            print_last_write_time(ftime);

            std::cout << std::endl;
		}
	}
}

int main(int argc, char ** argv)
{
	system("chcp 1251");

    std::filesystem::path folder;

    char folder_path[512];
    std::cout << "Enter the path to the folder: ";
    std::cin >> folder_path;
    folder = folder_path;
    if (!std::filesystem::exists(folder))
	{
		std::cerr << "Path " << folder << " does not exist.\n";

		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "Path " << folder.string() << " exists." << std::endl;
	}

	

	view_directory(folder);

	system("pause");

	return EXIT_SUCCESS;
}