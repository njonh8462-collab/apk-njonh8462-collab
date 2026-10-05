#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "WebAppNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" {

static jstring getAppInfo(JNIEnv *env, jobject /* thiz */) {
    std::string msg = "Built with C++ (JNI) - Native layer active";
    LOGI("getAppInfo called");
    return env->NewStringUTF(msg.c_str());
}

static jint getNativeVersion(JNIEnv *env, jobject /* thiz */) {
    return 1;
}

static JNINativeMethod gMethods[] = {
    {"getAppInfo", "()Ljava/lang/String;", (void*)getAppInfo},
    {"getNativeVersion", "()I", (void*)getNativeVersion},
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void * /* reserved */) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    jclass clazz = env->FindClass("com/example/webapp/MainActivity");
    if (clazz == nullptr) {
        LOGI("Failed to find MainActivity");
        return JNI_ERR;
    }
    if (env->RegisterNatives(clazz, gMethods, sizeof(gMethods)/sizeof(gMethods[0])) != JNI_OK) {
        LOGI("Failed to register natives");
        return JNI_ERR;
    }
    LOGI("JNI_OnLoad completed");
    return JNI_VERSION_1_6;
}

} // extern "C"
