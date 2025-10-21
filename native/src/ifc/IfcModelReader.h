#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace ifcjson {

struct ProjectMetadata {
    std::string id;
    std::string project_id;
    std::string author;
    std::string created_at;
    std::string schema;
    std::string creating_application;
};

class IfcModelReader {
public:
    IfcModelReader();
    ~IfcModelReader();

    void load_from_file(const std::string& path);
    void load_from_bytes(const std::vector<unsigned char>& bytes);

    [[nodiscard]] const ProjectMetadata& project_metadata() const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}  // namespace ifcjson
