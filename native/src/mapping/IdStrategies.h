#pragma once

#include <string>

namespace ifcjson {

std::string deterministic_hash_id(const std::string& seed);

}  // namespace ifcjson
