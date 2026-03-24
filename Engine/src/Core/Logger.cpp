




#include "Core/Logger.h"
#include <iomanip>

namespace LOGGER {

static std::string format_time(const std::chrono::system_clock::time_point& tp,
                               const char* fmt) {
    auto t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), fmt);
    return ss.str();
}

std::string Logger::CurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    return format_time(now, "%Y-%m-%d %H:%M:%S");
}

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

void Logger::Init(bool consoleLog, bool retainLogs) {
    assert(!m_bInitialized);
    m_bConsoleLog = consoleLog;
    m_bRetainLog = retainLogs;
    m_bInitialized = true;
}

} // namespace LOGGER
