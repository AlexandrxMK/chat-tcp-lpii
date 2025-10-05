#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

class Logger {
public:
    static Logger& getInstance();
    void log(const std::string& message);

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) =delete;

private:
    Logger();
    ~Logger();

    std::ofstream m_logFile;
    std::mutex m_mutex;
};

#endif 