#include "mapping/IdStrategies.h"

#include <iomanip>
#include <sstream>
#include <string>

namespace ifcjson {

std::string deterministic_hash_id(const std::string& seed) {
    std::hash<std::string> hasher;
    const auto value = hasher(seed);
    std::ostringstream oss;
    oss << "HASH_" << std::hex << std::setw(sizeof(size_t) * 2) << std::setfill('0') << value;
    return oss.str();
}

}  // namespace ifcjson
