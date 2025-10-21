#pragma once

#include <functional>
#include <mutex>
#include <string>

namespace ifcjson {

enum class LogLevel { kDebug, kInfo, kWarn, kError };

class Logger {
public:
    using Sink = std::function<void(LogLevel, const std::string&)>;

    static Logger& instance();

    void set_sink(Sink sink);
    void log(LogLevel level, const std::string& message);

private:
    Logger() = default;
    Sink sink_;
    std::mutex mutex_;
};

}  // namespace ifcjson
