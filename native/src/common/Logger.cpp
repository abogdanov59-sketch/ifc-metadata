#include "common/Logger.h"

#include <iostream>

namespace ifcjson {

Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::set_sink(Sink sink) {
    std::lock_guard<std::mutex> lock(mutex_);
    sink_ = std::move(sink);
}

void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (sink_) {
        sink_(level, message);
        return;
    }

    std::ostream& out = (level == LogLevel::kError) ? std::cerr : std::clog;
    out << message << std::endl;
}

}  // namespace ifcjson
