//
// Created by chris on 6/1/26.
//

#include "logger.h"

#include <iostream>
#include <fstream>
#include <filesystem>


logger::logger()
{
    return;

    auto time = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(time);

    std::filesystem::path dir = std::filesystem::current_path() / "Log";  // or build any path
    std::filesystem::path file = dir / std::ctime(&end_time);
    file_path = file;

    auto created_dir = std::filesystem::create_directories(dir);
    if (created_dir == true)
    {
        std::cout << "\n-----------\n" << "created new folder 'Log' see:\n" << file_path << "\n-----------";
    }

    std::ofstream new_file(file);
    log = std::move(new_file);

    if (!log)
    {
        std::cerr << "Error: could not open file!" << std::endl;
        return;
    }

    log << "[FILE CREATED] " << std::ctime(&end_time) << "\n\n";
    log.close();
}

logger::~logger()
{
    return;
    if (has_logged == false)
    {
        if (log)
        {
            std::cout << "\nnothing has been logged, deleting file: " << file_path;
            std::filesystem::remove(file_path);
        }
    }
}

bool logger::log_info(const std::string& info, const std::string& author)
{
    return true;
    if (debug_mode == false) return true;

    auto time = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(time);

    has_logged = true;
    std::ofstream log(file_path, std::fstream::app);

    log << "\n-----------\n"
        << "[INFO] by [" << author << "] at " << std::ctime(&end_time)
        << "\n[" << info << "]\n"
        << "\n-----------\n";

    log.flush();
    log.close();

    return true;
}

bool logger::log_error(const std::string& error, const std::string& author)
{
    return true;
    if (debug_mode == false) return true;
    auto time = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(time);

    has_logged = true;
    std::ofstream log(file_path, std::fstream::app);

    log << "\n-----------\n"
        << "[ERROR] by [" << author << "] at " << std::ctime(&end_time)
        << "\n[" << error << "]\n"
        << "\n-----------\n";

    log.flush();
    log.close();

    return true;
}



