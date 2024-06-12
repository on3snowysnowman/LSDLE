#pragma once

#include <vector>
#include <filesystem>
#include <fstream>
#include <cstdio>

class FileSystemHandler
{
public:

    static bool make_directory(std::string directory_path);

    static bool make_file(std::string file_path);

    static bool delete_file(std::string file_path);

    /**
     * Returns true if the 'path' parameter is a valid directory
     * 
     * @param directory_path Target Directory
    */
    static bool does_directory_exist(std::string directory_path);

    static std::vector<std::string> 
        get_files_at_directory(std::string directory_path);


private:

    static std::ofstream out_file_stream;
};