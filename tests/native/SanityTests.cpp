#include <iostream>
#include <vector>

#include "ifc/IfcModelReader.h"
#include "json/JsonWriter.h"
#include "mapping/MetaModelBuilder.h"

int main() {
    try {
        ifcjson::IfcModelReader reader;
        std::vector<unsigned char> buffer{'I', 'F', 'C'};
        reader.load_from_bytes(buffer);

        ifcjson::MetaModelBuilder builder;
        auto model = builder.build(reader);

        ifcjson::JsonWriter writer;
        const auto json = writer.write(model);
        std::cout << json << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Sanity test failed: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
