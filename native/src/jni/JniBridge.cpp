#include "jni/JniUtils.h"

#include <jni.h>

#include <memory>
#include <mutex>
#include <vector>

#include "common/Errors.h"
#include "common/Logger.h"
#include "ifc/IfcModelReader.h"
#include "json/JsonWriter.h"
#include "mapping/MetaModelBuilder.h"

using ifcjson::ErrorCode;
using ifcjson::IfcJsonException;
using ifcjson::IfcModelReader;
using ifcjson::JsonWriter;
using ifcjson::LogLevel;
using ifcjson::Logger;
using ifcjson::MetaModelBuilder;
using ifcjson::MetaModel;

namespace {

std::mutex g_mutex;
bool g_initialized = false;

struct ConverterContext {
    JsonWriter writer;
};

ConverterContext& context() {
    static ConverterContext ctx;
    return ctx;
}

}  // namespace

extern "C" JNIEXPORT void JNICALL
Java_com_example_ifc_IfcJsonConverter_initialize(JNIEnv* env, jclass, jstring options) {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (g_initialized) {
        return;
    }

    if (options) {
        ifcjson::JniStringGuard options_guard(env, options);
        Logger::instance().log(LogLevel::kInfo, std::string("Received options: ") + (options_guard.c_str() ? options_guard.c_str() : ""));
    }

    g_initialized = true;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_ifc_IfcJsonConverter_shutdown(JNIEnv*, jclass) {
    std::lock_guard<std::mutex> lock(g_mutex);
    g_initialized = false;
}

static std::string convert_from_reader(IfcModelReader& reader) {
    MetaModelBuilder builder;
    MetaModel model = builder.build(reader);
    return context().writer.write(model);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ifc_IfcJsonConverter_transformFromFile(JNIEnv* env, jclass, jstring path, jstring options) {
    if (!g_initialized) {
        ifcjson::throw_ifc_exception(env, "Converter not initialized", "INTERNAL_ERROR");
        return nullptr;
    }

    try {
        ifcjson::JniStringGuard path_guard(env, path);
        if (options) {
            ifcjson::JniStringGuard options_guard(env, options);
            Logger::instance().log(LogLevel::kDebug, std::string("transformFromFile options: ") + (options_guard.c_str() ? options_guard.c_str() : ""));
        }
        IfcModelReader reader;
        reader.load_from_file(path_guard.c_str() ? path_guard.c_str() : "");
        const auto json = convert_from_reader(reader);
        return env->NewStringUTF(json.c_str());
    } catch (const IfcJsonException& ex) {
        ifcjson::throw_ifc_exception(env, ex.what(), "IO_ERROR");
        return nullptr;
    } catch (const std::exception& ex) {
        ifcjson::throw_ifc_exception(env, ex.what(), "INTERNAL_ERROR");
        return nullptr;
    }
}

extern "C" JNIEXPORT jbyteArray JNICALL
Java_com_example_ifc_IfcJsonConverter_transformFromBytes(JNIEnv* env, jclass, jbyteArray data, jstring options) {
    if (!g_initialized) {
        ifcjson::throw_ifc_exception(env, "Converter not initialized", "INTERNAL_ERROR");
        return nullptr;
    }

    try {
        if (options) {
            ifcjson::JniStringGuard options_guard(env, options);
            Logger::instance().log(LogLevel::kDebug, std::string("transformFromBytes options: ") + (options_guard.c_str() ? options_guard.c_str() : ""));
        }

        jsize length = env->GetArrayLength(data);
        std::vector<unsigned char> buffer(length);
        env->GetByteArrayRegion(data, 0, length, reinterpret_cast<jbyte*>(buffer.data()));

        IfcModelReader reader;
        reader.load_from_bytes(buffer);
        const auto json = convert_from_reader(reader);

        jbyteArray result = env->NewByteArray(static_cast<jsize>(json.size()));
        env->SetByteArrayRegion(result, 0, static_cast<jsize>(json.size()), reinterpret_cast<const jbyte*>(json.data()));
        return result;
    } catch (const IfcJsonException& ex) {
        ifcjson::throw_ifc_exception(env, ex.what(), "PARSE_ERROR");
        return nullptr;
    } catch (const std::exception& ex) {
        ifcjson::throw_ifc_exception(env, ex.what(), "INTERNAL_ERROR");
        return nullptr;
    }
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ifc_IfcJsonConverter_getVersion(JNIEnv* env, jclass) {
    if (!g_initialized) {
        ifcjson::throw_ifc_exception(env, "Converter not initialized", "INTERNAL_ERROR");
        return nullptr;
    }

    const char* version = "ifcjsonconverter-native/0.1.0";
    return env->NewStringUTF(version);
}
