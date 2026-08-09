/**
 * NativeTemplate.cpp
 *
 * Thin JNI bridge between the Java/Android layer and the shared Triangle renderer.
 * All GL logic lives in Scene/Triangle.h + Triangle.cpp.
 *
 * Native method signatures match MainActivity.java:
 *   package com.example.glpiframeworkintro
 *   class   MainActivity
 */

#define LOG_TAG "GLPIFrameworkIntroNative"

#include <jni.h>
#include "Triangle.h"   // brings in Platform.h → GLES3/gl3.h + LOGI/LOGE

static Triangle g_triangle;

// ---------------------------------------------------------------------------
// JNI entry points
// ---------------------------------------------------------------------------

extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_helloworldandroid_MainActivity_nativeInit(
        JNIEnv* /*env*/, jobject /*thiz*/, jobject /*assetManager*/)
{
    LOGI("nativeInit called");
    g_triangle.InitModel();
    return JNI_TRUE;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_helloworldandroid_MainActivity_nativeResize(
        JNIEnv* /*env*/, jobject /*thiz*/, jint width, jint height)
{
    g_triangle.Resize(width, height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_helloworldandroid_MainActivity_nativeRender(
        JNIEnv* /*env*/, jobject /*thiz*/)
{
    g_triangle.Render();
}
