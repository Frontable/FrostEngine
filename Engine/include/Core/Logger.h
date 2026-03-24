

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

namespace LOGGER
{

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
        std::string log{};
    };

    struct LogTime
    {
        std::string year, month, day, hour, minute, second;
    };

    class Logger
    {
    private:
        std::vector<LogEntry> m_LogEntries;
        bool m_bInitialized{false};
        bool m_bConsoleLog{true};
        bool m_bRetainLog{true};
        LogTime m_logTime;

        Logger() = default;
        std::string CurrentDateTime();

        template <typename... Args>
        std::string StringFormat(const char *fmt, Args... args)
        {
            char buffer[1024];
            std::snprintf(buffer, sizeof(buffer), fmt, args...);
            return buffer;
        }

    public:
        static Logger &GetInstance();

        void Init(bool consoleLog = true, bool retainLogs = true);

        template <typename... Args>
        void Log(const std::string &message, Args &&...args)
        {
            assert(m_bInitialized);
            std::stringstream ss;
            ss << "[INFO]: " << CurrentDateTime() << " - "
               << StringFormat(message.c_str(), std::forward<Args>(args)...) << "\n";

            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, GREEN);
            if (m_bConsoleLog)
                std::cout << ss.str();
            SetConsoleTextAttribute(h, WHITE);

            if (m_bRetainLog)
                m_LogEntries.push_back({LogEntry::LogType::INFO, ss.str()});
        }

        template <typename... Args>
        void Warn(const std::string &message, Args &&...args)
        {
            assert(m_bInitialized);
            std::stringstream ss;
            ss << "[WARN]: " << CurrentDateTime() << " - "
               << StringFormat(message.c_str(), std::forward<Args>(args)...) << "\n";

            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, YELLOW);
            if (m_bConsoleLog)
                std::cout << ss.str();
            SetConsoleTextAttribute(h, WHITE);

            if (m_bRetainLog)
                m_LogEntries.push_back({LogEntry::LogType::WARN, ss.str()});
        }

        template <typename... Args>
        void Error(const SourceInfo &src, const std::string &message, Args &&...args)
        {
            assert(m_bInitialized);
            std::stringstream ss;
            ss << "[ERROR]: " << CurrentDateTime() << " - "
               << StringFormat(message.c_str(), std::forward<Args>(args)...)
               << "\nFUNC: " << src.function
               << "\nLINE: " << src.line
               << "\nFILE: " << src.file << "\n\n";

            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, RED);
            if (m_bConsoleLog)
                std::cout << ss.str();
            SetConsoleTextAttribute(h, WHITE);

            if (m_bRetainLog)
                m_LogEntries.push_back({LogEntry::LogType::ERR, ss.str()});
        }
    };

} // namespace LOGGER

#define FROST_LOG(...) LOGGER::Logger::GetInstance().Log(__VA_ARGS__)
#define FROST_WARN(...) LOGGER::Logger::GetInstance().Warn(__VA_ARGS__)
#define FROST_ERROR(...) LOGGER::Logger::GetInstance().Error(LOGGER::CURRENT_SOURCE, __VA_ARGS__)
#define FROST_INIT_LOG(console, retain) LOGGER::Logger::GetInstance().Init(console, retain)
