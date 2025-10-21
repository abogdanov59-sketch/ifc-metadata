#include "jni/JniUtils.h"

namespace ifcjson {

JniStringGuard::JniStringGuard(JNIEnv* env, jstring str)
    : env_(env), str_(str), chars_(nullptr) {
    if (str_) {
        chars_ = env_->GetStringUTFChars(str_, nullptr);
    }
}

JniStringGuard::~JniStringGuard() {
    if (str_ && chars_) {
        env_->ReleaseStringUTFChars(str_, chars_);
    }
}

const char* JniStringGuard::c_str() const { return chars_; }

void throw_ifc_exception(JNIEnv* env, const char* message, const char* code) {
    jclass exceptionClass = env->FindClass("com/example/ifc/IfcConversionException");
    if (!exceptionClass) {
        env->ThrowNew(env->FindClass("java/lang/RuntimeException"), message);
        return;
    }

    jmethodID ctor = env->GetMethodID(exceptionClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;)V");
    if (!ctor) {
        env->ThrowNew(exceptionClass, message);
        return;
    }

    jstring jMessage = env->NewStringUTF(message ? message : "");
    jstring jCode = env->NewStringUTF(code ? code : "INTERNAL_ERROR");
    jobject exception = env->NewObject(exceptionClass, ctor, jCode, jMessage);
    env->Throw(reinterpret_cast<jthrowable>(exception));
}

}  // namespace ifcjson
