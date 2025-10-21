#pragma once

#include <string>

#include "mapping/MetaModelBuilder.h"

namespace ifcjson {

class JsonWriter {
public:
    JsonWriter();
    ~JsonWriter();

    std::string write(const MetaModel& model) const;
};

}  // namespace ifcjson
