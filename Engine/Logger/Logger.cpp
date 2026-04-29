#include "Logger.h"
#include <iomanip>

namespace LOGGER {

std::string format_time_point(const std::chrono::system_clock::time_point &tp,
                              const std::string &format)
{
    auto time_t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), format.c_str());
    return ss.str();
}

std::string Logger::CurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    m_logTime.year = format_time_point(now, "%Y");
    std::string month = format_time_point(now, "%B");
    std::string dayNumber = format_time_point(now, "%d");
    std::string hour = format_time_point(now, "%H");
    std::string minute = format_time_point(now, "%M");
    std::string second = format_time_point(now, "%S");
    std::ostringstream oss;
    oss << m_logTime.year << " - " << month << " - " << dayNumber << " - " << hour << " - " << minute << " - " << second;

    return oss.str();
}

Logger &Logger::GetInstance()
{
    static Logger instance{};
    return instance;
}

void Logger::Init(bool consoleLog, bool retainLogs)
{
    assert(!m_bInitialized && "Do not call Initialize more than once!");
    if (m_bInitialized)
    {
        std::cout << "Logger has already been Initialized!" << std::endl;
        return;
    }

    m_bConsoleLog = consoleLog;
    m_bRetainLog = retainLogs;
    m_bInitialized = true;
}

} // namespace LOGGER
