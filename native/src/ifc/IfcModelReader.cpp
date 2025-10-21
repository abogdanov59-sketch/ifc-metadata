#include "ifc/IfcModelReader.h"

#include <fstream>

#include "common/Errors.h"
#include "common/Logger.h"
#include "common/Utils.h"

namespace ifcjson {

struct IfcModelReader::Impl {
    ProjectMetadata metadata;
    bool loaded = false;
};

IfcModelReader::IfcModelReader() : impl_(std::make_unique<Impl>()) {}

IfcModelReader::~IfcModelReader() = default;

void IfcModelReader::load_from_file(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw IfcJsonException(ErrorCode::kIoError, "Unable to open IFC file: " + path);
    }

    impl_->metadata = ProjectMetadata{path, "UNKNOWN", "", current_timestamp_utc(), "IFC4", "Unknown"};
    impl_->loaded = true;
    Logger::instance().log(LogLevel::kDebug, "Loaded IFC file stub: " + path);
}

void IfcModelReader::load_from_bytes(const std::vector<unsigned char>& bytes) {
    if (bytes.empty()) {
        throw IfcJsonException(ErrorCode::kParseError, "Empty IFC byte buffer");
    }

    impl_->metadata = ProjectMetadata{"IN_MEMORY", "UNKNOWN", "", current_timestamp_utc(), "IFC4", "Unknown"};
    impl_->loaded = true;
    Logger::instance().log(LogLevel::kDebug, "Loaded IFC bytes stub (" + std::to_string(bytes.size()) + " bytes)");
}

const ProjectMetadata& IfcModelReader::project_metadata() const {
    if (!impl_->loaded) {
        throw IfcJsonException(ErrorCode::kInternalError, "Model not loaded");
    }
    return impl_->metadata;
}

}  // namespace ifcjson
