#pragma once

#include <map>
#include <string>

#include "ifc/IfcModelReader.h"
#include "ifc/IfcTraverser.h"

namespace ifcjson {

struct MetaModel {
    ProjectMetadata metadata;
    MetaObjectMap objects;
};

class MetaModelBuilder {
public:
    MetaModelBuilder();
    ~MetaModelBuilder();

    MetaModel build(const IfcModelReader& reader);
};

}  // namespace ifcjson
