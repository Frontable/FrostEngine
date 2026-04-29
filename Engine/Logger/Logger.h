#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <cassert>
#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>
#include <Windows.h>

namespace LOGGER {

constexpr WORD GREEN = 2;
constexpr WORD RED = 4;
constexpr WORD YELLOW = 6;
constexpr WORD WHITE = 7;

struct SourceInfo
{
    const char *file;
    int line;
    const char *function;

    SourceInfo(const char *f, int l, const char *fn)
        : file(f), line(l), function(fn) {}
};

#define CURRENT_SOURCE SourceInfo(__FILE__, __LINE__, __func__)

struct LogEntry
{
    enum class LogType
    {
        INFO,
        WARN,
        ERR,
        NONE
    };
    LogType type{LogType::INFO};
    std::string log{""};
};

struct LogTime
{
    std::string day, dayNumber, month, year, hour, minute, second;
};

class Logger
{
private:
    std::string day;
    std::vector<LogEntry> m_LogEntries;
    bool m_bLogAdded{false}, m_bInitialized{false}, m_bConsoleLog{true}, m_bRetainLog{true};
    LogTime m_logTime;
    Logger() = default;

    std::string CurrentDateTime();

    template <typename... Args>
    std::string StringFormat(const char *fmt, Args... args)
    {
        char buffer[1024];
        std::snprintf(buffer, sizeof(buffer), fmt, args...);
        return std::string(buffer);
    }

public:
    static Logger &GetInstance();

    ~Logger() = default;
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    void Init(bool consoleLog = true, bool retainLogs = true);

    template <typename... Args>
    void Log(const std::string &message, Args &&...args)
    {
        assert(m_bInitialized && "Logger must be Initialized before being used!");
        if (!m_bInitialized)
        {
            std::cout << "Logger must be Initialized before being used!" << std::endl;
            return;
        }

        std::stringstream ss;
        ss << "[INFO]: " << CurrentDateTime() << " - "
           << StringFormat(message.c_str(), std::forward<Args>(args)...) << "\n";

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, GREEN);
        if (m_bConsoleLog)
            std::cout << ss.str();
        SetConsoleTextAttribute(hConsole, WHITE);

        if (m_bRetainLog)
            m_LogEntries.emplace_back(LogEntry{LogEntry::LogType::INFO, ss.str()});
    }

    template <typename... Args>
    void Warn(const std::string &message, Args &&...args)
    {
        assert(m_bInitialized && "Logger must be Initialized before being used!");

        if (!m_bInitialized)
        {
            std::cout << "Logger must be Initialized before being used!" << std::endl;
            return;
        }

        std::stringstream ss;
        ss << "[WARN]: " << CurrentDateTime() << " - "
           << StringFormat(message.c_str(), std::forward<Args>(args)...) << "\n";

        if (m_bConsoleLog)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, YELLOW);
            std::cout << ss.str();
            SetConsoleTextAttribute(hConsole, WHITE);
        }

        if (m_bRetainLog)
        {
            m_LogEntries.emplace_back(LogEntry{LogEntry::LogType::WARN, ss.str()});
        }
    }

    template <typename... Args>
    void Error(const SourceInfo &src, const std::string &message, Args &&...args)
    {
        assert(m_bInitialized && "Logger must be Initialized before being used!");
        if (!m_bInitialized)
        {
            std::cout << "Logger must be Initialized before being used!" << std::endl;
            return;
        }

        std::stringstream ss;
        ss << "[ERROR]: " << CurrentDateTime() << " - "
           << StringFormat(message.c_str(), std::forward<Args>(args)...)
           << "\nFUNC: " << src.function
           << "\nLINE: " << src.line
           << "\nFILE: " << src.file << "\n\n";

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, RED);
        if (m_bConsoleLog)
            std::cout << ss.str();
        SetConsoleTextAttribute(hConsole, WHITE);

        if (m_bRetainLog)
            m_LogEntries.emplace_back(LogEntry{LogEntry::LogType::ERR, ss.str()});
    }

    bool IsInitialized() const noexcept { return m_bInitialized; }
};

} // namespace LOGGER

// Macros kept global for convenience (use after including Logger.h)
#define FROST_LOG(x, ...) LOGGER::Logger::GetInstance().Log(x, ##__VA_ARGS__);
#define FROST_WARN(x, ...) LOGGER::Logger::GetInstance().Warn(x, ##__VA_ARGS__);
#define FROST_ERROR(x, ...) LOGGER::Logger::GetInstance().Error(LOGGER::CURRENT_SOURCE, x, ##__VA_ARGS__);
#define FROST_INIT_LOG(console, retain) LOGGER::Logger::GetInstance().Init(console, retain);
