cmake_minimum_required(VERSION 3.16)

project(ifcjsonconverter LANGUAGES CXX)

option(BUILD_SHARED_LIB "Build shared library" ON)
option(BUILD_TESTS "Build tests" ON)
option(WITH_IFC_OPENSHELL "Enable IfcOpenShell integration" OFF)
option(WITH_RAPIDJSON "Enable RapidJSON based writer" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ifcjsonconverter
    src/ifc/IfcModelReader.cpp
    src/ifc/IfcTraverser.cpp
    src/mapping/MetaModelBuilder.cpp
    src/mapping/IdStrategies.cpp
    src/json/JsonWriter.cpp
    src/jni/JniBridge.cpp
    src/jni/JniUtils.cpp
    src/common/Errors.cpp
    src/common/Logger.cpp
    src/common/Utils.cpp
)

target_include_directories(ifcjsonconverter
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

if(WITH_IFC_OPENSHELL)
    message(STATUS "IfcOpenShell integration is enabled. Make sure to add the required include directories and libraries.")
endif()

if(WITH_RAPIDJSON)
    find_path(RAPIDJSON_INCLUDE_DIR rapidjson/document.h)
    if(RAPIDJSON_INCLUDE_DIR)
        target_compile_definitions(ifcjsonconverter PRIVATE IFCJSON_HAVE_RAPIDJSON=1)
        target_include_directories(ifcjsonconverter PRIVATE ${RAPIDJSON_INCLUDE_DIR})
    else()
        message(WARNING "RapidJSON headers not found. Falling back to stub JSON writer implementation.")
    endif()
endif()

# JNI headers
find_package(Java COMPONENTS Development)
find_package(JNI)
if(JNI_FOUND)
    target_include_directories(ifcjsonconverter PUBLIC ${JNI_INCLUDE_DIRS})
else()
    message(WARNING "JNI headers not found. JNI bridge will only compile in limited environments.")
endif()

if(BUILD_SHARED_LIB)
    set_target_properties(ifcjsonconverter PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
    )
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
