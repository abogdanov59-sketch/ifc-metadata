#pragma once

#include <map>
#include <string>
#include <vector>

namespace ifcjson {

struct MetaObject {
    std::string id;
    std::string name;
    std::string type;
    std::string parent;
    std::vector<std::string> properties;
    std::string material_id;
    std::string type_id;
};

using MetaObjectMap = std::map<std::string, MetaObject>;

class IfcTraverser {
public:
    IfcTraverser();
    ~IfcTraverser();

    MetaObjectMap build_stub_hierarchy();
};

}  // namespace ifcjson
