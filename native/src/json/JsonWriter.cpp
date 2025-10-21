#include "json/JsonWriter.h"

#include <sstream>

namespace ifcjson {

JsonWriter::JsonWriter() = default;
JsonWriter::~JsonWriter() = default;

std::string JsonWriter::write(const MetaModel& model) const {
    std::ostringstream oss;
    oss << "{\n";
    oss << "  \"id\": \"" << model.metadata.id << "\",\n";
    oss << "  \"projectId\": \"" << model.metadata.project_id << "\",\n";
    oss << "  \"author\": \"" << model.metadata.author << "\",\n";
    oss << "  \"createdAt\": \"" << model.metadata.created_at << "\",\n";
    oss << "  \"schema\": \"" << model.metadata.schema << "\",\n";
    oss << "  \"creatingApplication\": \"" << model.metadata.creating_application << "\",\n";
    oss << "  \"metaObjects\": {";
    bool first = true;
    for (const auto& [guid, object] : model.objects) {
        if (!first) {
            oss << ",";
        }
        first = false;
        oss << "\n    \"" << guid << "\": {";
        oss << "\"id\": \"" << object.id << "\", ";
        oss << "\"name\": \"" << object.name << "\", ";
        oss << "\"type\": \"" << object.type << "\", ";
        if (!object.parent.empty()) {
            oss << "\"parent\": \"" << object.parent << "\", ";
        } else {
            oss << "\"parent\": null, ";
        }
        oss << "\"properties\": [";
        for (size_t i = 0; i < object.properties.size(); ++i) {
            if (i != 0) {
                oss << ", ";
            }
            oss << "\"" << object.properties[i] << "\"";
        }
        oss << "], ";
        if (!object.material_id.empty()) {
            oss << "\"material_id\": \"" << object.material_id << "\", ";
        } else {
            oss << "\"material_id\": null, ";
        }
        if (!object.type_id.empty()) {
            oss << "\"type_id\": \"" << object.type_id << "\"";
        } else {
            oss << "\"type_id\": null";
        }
        oss << "}";
    }
    if (!model.objects.empty()) {
        oss << "\n  ";
    }
    oss << "}\n";
    oss << "}\n";
    return oss.str();
}

}  // namespace ifcjson
