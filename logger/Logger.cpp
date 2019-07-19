//
// Created by vasilis on 3/6/2019.
//

#include "Logger.h"
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;

/**
 * A singleton method  that returns a static instance of logger .Static variables instantiate only once.
 * So we can use this pattern instead the traditional approach like to check if the instance of Logger is nullptr.
 * @return an instance of logger
 */
Logger& Logger::instance()
{
    static Logger instance;
    return instance;
}

Logger::Logger()=default;

Logger::~Logger()=default;

void Logger::setLogLevel(LogLevel level)
{
    mLogLevel = level;
}
/**
 * takes the current time of system and after convert it as arithmetic type in order to produce and print a local time.
 * @see <a href=https://en.cppreference.com/w/cpp/chrono/c/localtime>local_time</a>
 */
 void Logger::print_time()
{
    auto now = std::chrono::system_clock::now();
    auto stime = std::chrono::system_clock::to_time_t(now);
    auto ltime = std::localtime(&stime);

    std::cout << std::put_time(ltime, "%c");
}
/**
 *
 * @param level
 * @return string_view .Non modifiable string !
 */
string_view Logger::getLogLevelString(LogLevel level) const
{
    switch (level) {
        case LogLevel::Error:
            return "ΣΦΑΛΜΑ";
        case LogLevel::Info:
            return "ΠΛΗΡΟΦΟΡΙΑ";
    }
//    throw runtime_error("Invalid log level.");
}

/**
 * For a single std::string STL message.
 * @param message
 * @param logLevel .The log level like ERROR or INFO
 */
void Logger::log(string_view message, LogLevel logLevel)
{
    if (mLogLevel < logLevel) {
        return;
    }

    print_time();
    std::cout<<" ";
    std::cout<<"["<< getLogLevelString(logLevel).data()<<"]"
             << ": "<< message << endl;
}

/**
 * If we have a vector pool of messages , use this function istead .
 * @param messages .A vector of std::string that holds messages
 * @param logLevel
 */
void Logger::log(const vector<string>& messages, LogLevel logLevel)
{
    if (mLogLevel < logLevel) {
        return;
    }
//iterate over the vector
    for (const auto& message : messages) {
        log(message, logLevel);
    }
}
