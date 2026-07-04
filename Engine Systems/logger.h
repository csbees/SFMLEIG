//
// Created by chris on 6/1/26.
//

#ifndef ERROR_LOGGER_H
#define ERROR_LOGGER_H
#include <string>
#include <fstream>
#include <iostream>

class logger
{
public:
    /// @brief Logs an error in the log
    /// @param error The error you want to log
    /// @param author Where the error is coming from. Go functions, systems, objects, files.
    bool log_error(const std::string& error,const std::string& author);
    /// @brief Logs info in the log
    /// @param info The info you want to log
    /// @param author Where the error is coming from. Go functions, systems, objects, files.
    bool log_info(const std::string& info, const std::string& author);

    logger();
    ~logger();
private:
    // if the logger has logged an error, the file for storing logged errors will not be destroyed, otherwise it will be.
    bool has_logged = false;

    // turn off to stop the logger.
    bool debug_mode = true;
    std::ofstream log;
    std::filesystem::path file_path;
};

#endif //ERROR_LOGGER_H
