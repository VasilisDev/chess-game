//
// Created by vasilis on 3/6/2019.
//

#ifndef UNTITLED23_LOGGER_H
#define UNTITLED23_LOGGER_H

#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <string_view>

// Definition of a singleton logger class.
class Logger final
{
public:
    enum class LogLevel {
        Error,
        Info
    };

    // Returns a reference to the singleton Logger object.
    static Logger& instance();

    // Prevent copy/move construction.
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;

    // Prevent copy/move assignment operations.
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

    // Sets the log level.
    void setLogLevel(LogLevel level);

    // Logs a single message at the given log level.
    void log(std::string_view message, LogLevel logLevel);

    // Logs a vector of messages at the given log level.
    void log(const std::vector<std::string>& messages,
             LogLevel logLevel);
    void print_time();

private:
    // Private constructor and destructor.
     Logger();
    ~Logger();

    // Converts a log level to a human readable Board.
    std::string_view getLogLevelString(LogLevel level) const;

    LogLevel mLogLevel = LogLevel::Error;
};



#endif //UNTITLED23_LOGGER_H
