#include "logger.h"
#include <chrono>
#include <iomanip>
#include <sstream>

Logger::Logger() {
    m_logFile.open("log.txt", std::ios::out | std::ios::app);
    if (!m_logFile.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo de log." << std::endl;
    }
}

Logger::~Logger() {
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(m_mutex);

    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    std::tm tm_buf;
    localtime_r(&time_t_now, &tm_buf);
    
    if (m_logFile.is_open()) {
        m_logFile << std::put_time(&tm_buf, "[%Y-%m-%d %H:%M:%S] ") << message << std::endl;
    }
}