#include "common/Utils.h"

#include <iomanip>
#include <sstream>

namespace ifcjson {

std::string current_timestamp_utc() {
    using clock = std::chrono::system_clock;
    const auto now = clock::now();
    const auto time = clock::to_time_t(now);
    std::tm tm{};
#if defined(_WIN32)
    gmtime_s(&tm, &time);
#else
    gmtime_r(&time, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
    return oss.str();
}

}  // namespace ifcjson
