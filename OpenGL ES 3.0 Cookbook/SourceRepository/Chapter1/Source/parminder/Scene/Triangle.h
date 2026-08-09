#pragma once

/**
 * Triangle.h
 *
 * Self-contained rotating triangle renderer (shader, VAO, VBOs).
 * Used by Desktop (Windows/GLFW) and Emscripten builds.
 * Android uses NativeTemplate.cpp (monolithic JNI) instead.
 */

#include "Platform.h"

class Triangle {
public:
    Triangle();
    ~Triangle();

    void InitModel();
    void Render();
    void Resize(int w, int h);

private:
    GLuint programID    = 0;
    GLuint vao          = 0;
    GLuint vboPos       = 0;
    GLuint vboColor     = 0;
    GLint  uRadianAngle = -1;
    float  degree       = 0.0f;
};
