#pragma once

#include <jni.h>

#include <string>

namespace ifcjson {

class JniStringGuard {
public:
    JniStringGuard(JNIEnv* env, jstring str);
    ~JniStringGuard();

    JniStringGuard(const JniStringGuard&) = delete;
    JniStringGuard& operator=(const JniStringGuard&) = delete;

    [[nodiscard]] const char* c_str() const;

private:
    JNIEnv* env_;
    jstring str_;
    const char* chars_;
};

void throw_ifc_exception(JNIEnv* env, const char* message, const char* code);

}  // namespace ifcjson
