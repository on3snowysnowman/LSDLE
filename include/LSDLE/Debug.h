#pragma once

#include <fstream>
#include <filesystem>
#include <cstdint>


/**
 * @brief Handles code output to a text file. 
 * 
 * Can be used for debugging, or general info output from the program. 
 * Should be cleared using the 'clear_debug_output_file' per each execution 
 * of the program, so the output data is not appended onto old executions.
*/
class Debug
{

public:

    enum THREAT_LEVEL : uint8_t
    {
        LOG,
        WARN,
        ERR
    };

    /**
     * Returns true if the 'path' parameter is a valid directory
     * 
     * @param path Target Directory
    */
    static bool does_directory_exist(const char* path)
    {
        return std::filesystem::exists(path);
    }

    /**
     * Clears the Debug's output file
    */
    static void clear_debug_output_file()
    {
        file_stream.open(output_file_path, std::ios::out);
        file_stream.close();
        file_stream.clear();
    }

    /**
     * Logs the 'content' to the output file, with the passed threat level
     * as a prefix. For instance, if the threat level is set to 'LOG', "[LOG] "
     * will be outputted directly before the content.
     * 
     * @param content Text to be outputted 
     * @param level Threat level of the content
    */
    static void log(std::string content, THREAT_LEVEL level = LOG)
    {
        file_stream.open(output_file_path, std::ios::app);

        if(file_stream.is_open())
        {

            // Handle the threat level of the output

            switch(level)
            {
                case LOG:

                    file_stream << "[LOG] ";
                    break;

                case WARN:

                    file_stream << "[WARN] ";
                    break;

                case ERR:

                    file_stream << "[ERR] ";
                    break;
            }

            // Trim the string so that each line doesn't exceed 80 characters

            uint8_t line_length_limit = 74;

            if(content.size() > line_length_limit)
            {
                while(content.size() > line_length_limit)
                {
                    file_stream << content.substr(0, line_length_limit) 
                        << "\n      ";
                    content = content.substr(line_length_limit, content.size() 
                        - line_length_limit);
                }
            }

            // Output the final trim of the string, or the full string if it 
            // is less than 80 characters

            file_stream << content << '\n';
            file_stream.close();
        }
    }

    /**
     * @brief Changes the output directory to a new directory.
     * 
     * @param new_path New directory
     */
    static void change_output_directory(const char* new_path)
    {
        output_file_path = new_path;
    }

private:

    inline static std::fstream file_stream;
    inline static const char* output_file_path = "OutputLog.txt"; 

};