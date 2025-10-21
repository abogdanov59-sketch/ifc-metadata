add_executable(ifcjsonconverter_tests
    ../../tests/native/SanityTests.cpp
)

target_link_libraries(ifcjsonconverter_tests PRIVATE ifcjsonconverter)

add_test(NAME IfcJsonConverterSanity COMMAND ifcjsonconverter_tests)
