#pragma once

#include <exception>
#include <string>

namespace ifcjson {

enum class ErrorCode {
    kOk = 0,
    kIoError,
    kParseError,
    kUnsupportedSchema,
    kMappingError,
    kSerializationError,
    kInternalError
};

class IfcJsonException : public std::exception {
public:
    IfcJsonException(ErrorCode code, std::string message);

    [[nodiscard]] ErrorCode code() const noexcept;
    [[nodiscard]] const char* what() const noexcept override;

private:
    ErrorCode code_;
    std::string message_;
};

}  // namespace ifcjson
