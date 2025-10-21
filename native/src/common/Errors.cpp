#include "common/Errors.h"

namespace ifcjson {

IfcJsonException::IfcJsonException(ErrorCode code, std::string message)
    : code_(code), message_(std::move(message)) {}

ErrorCode IfcJsonException::code() const noexcept { return code_; }

const char* IfcJsonException::what() const noexcept { return message_.c_str(); }

}  // namespace ifcjson
