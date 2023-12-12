#pragma once

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Debug.h"
#include "Json.h"

/**
 * @brief Handles loading from and dumping to json files.
 * 
 */
class JsonLoader
{

public:

    /**
     * @brief Returns a json object with the contents from the file at 'path'
     * 
     * @param path Path to the json file
    */
    static Json get(const char* path)
    {

        // Check if the directory is valid
        if(!Debug::does_directory_exist(path))
        {
            std::string message = "JsonLoader.get(const char* "
                "path) where 'path' = " + std::string(path) + " -> Could not "
                "open file.";
            
            Debug::log(message, Debug::ERR);
            exit(1);
        }

        Json json_obj;

        file_stream.open(path, std::ios::in);

        if(file_stream.is_open())
        {
            // Fill the json obj with the file contents
            file_stream >> json_obj;

            file_stream.close();
        }

        return json_obj;
    }

    /**
     * @brief Dumps the contents of the 'json_obj' to a json file
     * 
     * @param json_obj Json object
     * @param path Path to the json file
    */
    static void dump(Json& json_obj, const char* path)
    {

        file_stream.open(path, std::ios::out);

        if(file_stream.is_open())
        {
            // Dump the contents of the json object into the json file
            file_stream << json_obj.dump(4);
            file_stream.close();
        }
    }


    /**
     * @brief Clears the passed json file. 
     * 
     * @param path Path to the json file
    */
    static void clear(const char* path)
    {
        // Check if the directory is valid
        if(!Debug::does_directory_exist(path))
        {
            std::string message = "JsonLoader.clear(const char* path) where "
                "'path' = " + std::string(path) + " -> Could not open file.";

            Debug::log(message, Debug::ERR);
            exit(1);
        }

        file_stream.open(path, std::ios::in);

        if(file_stream.is_open())
        {
            // Place an empty json object inside the file
            file_stream << Json::object({});
            file_stream.close();
        }
    }

private:

    inline static std::fstream file_stream;

};
