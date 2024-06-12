#include "FileSystemHandler.h"


// Static Members

std::ofstream FileSystemHandler::out_file_stream;

// Public

bool FileSystemHandler::make_directory(std::string directory_path)
{
    return std::filesystem::create_directory(directory_path);
}

bool FileSystemHandler::make_file(std::string file_path)
{
    out_file_stream.open(file_path);

    if(!out_file_stream.is_open())
    {
        return false;
    }

    out_file_stream.close();

    return true;
}

bool FileSystemHandler::delete_file(std::string file_path)
{
    return (std::remove(file_path.c_str()) == 0);
}

bool FileSystemHandler::does_directory_exist(std::string directory_path)
{
    return std::filesystem::exists(directory_path);
}

std::vector<std::string> 
        FileSystemHandler::get_files_at_directory(std::string directory_path)
{
    std::vector<std::string> file_paths;

    // Iterate through each save file in the directory
    for(const auto& save :
        std::filesystem::directory_iterator(directory_path))
    {
        file_paths.push_back(save.path().string());
    }

    return file_paths;
}


