#include "mapping/MetaModelBuilder.h"

namespace ifcjson {

MetaModelBuilder::MetaModelBuilder() = default;
MetaModelBuilder::~MetaModelBuilder() = default;

MetaModel MetaModelBuilder::build(const IfcModelReader& reader) {
    MetaModel model;
    model.metadata = reader.project_metadata();
    IfcTraverser traverser;
    model.objects = traverser.build_stub_hierarchy();
    return model;
}

}  // namespace ifcjson
