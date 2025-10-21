#include "ifc/IfcTraverser.h"

namespace ifcjson {

IfcTraverser::IfcTraverser() = default;
IfcTraverser::~IfcTraverser() = default;

MetaObjectMap IfcTraverser::build_stub_hierarchy() {
    MetaObjectMap map;
    MetaObject project{"PROJECT_GUID", "Stub Project", "IfcProject", "", {}, "", ""};
    map.emplace(project.id, project);
    MetaObject site{"SITE_GUID", "Stub Site", "IfcSite", project.id, {}, "", ""};
    map.emplace(site.id, site);
    return map;
}

}  // namespace ifcjson
