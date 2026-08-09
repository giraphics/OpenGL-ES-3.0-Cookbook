/**
 * main.cpp
 *
 * Entry point for Desktop (Windows/GLFW) and WebGL (Emscripten) builds.
 * Android uses NativeTemplate.cpp + JNI instead of this file.
 *
 * Emscripten supports two windowing backends (selected at compile time):
 *   USE_GLFW defined  → GLFW via -s USE_GLFW=3  (default, recommended)
 *   USE_GLFW absent   → SDL2 via -s USE_SDL=2
 *
 * The triangle rotates automatically – no user interaction required.
 * This is the introductory GLPI Framework demo.
 *
 * Ported from OpenGL ES 3.0 Cookbook – Chapter 2, GLPI Framework Intro.
 */

#include "Platform.h"
#include "Triangle.h"

static Triangle g_triangle;

// ==========================================================================
// WebGL / Emscripten
// ==========================================================================
#ifdef PLATFORM_EMSCRIPTEN

// --------------------------------------------------------------------------
// GLFW backend (default – build with -DUSE_GLFW -s USE_GLFW=3)
// --------------------------------------------------------------------------
#ifdef USE_GLFW

static GLFWwindow* g_window = nullptr;

static void fbsize_cb(GLFWwindow* /*win*/, int w, int h)
{
    g_triangle.Resize(w, h);
}

static void main_loop()
{
    if (glfwWindowShouldClose(g_window)) {
        emscripten_cancel_main_loop();
        glfwDestroyWindow(g_window);
        glfwTerminate();
        return;
    }
    glfwPollEvents();
    g_triangle.Render();
    glfwSwapBuffers(g_window);
}

int main()
{
    LOGI("GLPI Framework Intro - WebGL / Emscripten (GLFW)");

    if (!glfwInit()) { LOGE("glfwInit failed"); return -1; }

    glfwWindowHint(GLFW_CLIENT_API,            GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    g_window = glfwCreateWindow(800, 600, "GLPI Framework Intro", nullptr, nullptr);
    if (!g_window) { LOGE("glfwCreateWindow failed"); glfwTerminate(); return -1; }

    glfwMakeContextCurrent(g_window);
    glfwSetFramebufferSizeCallback(g_window, fbsize_cb);

    g_triangle.InitModel();
    int w, h;
    glfwGetFramebufferSize(g_window, &w, &h);
    g_triangle.Resize(w, h);

    emscripten_set_main_loop(main_loop, 0, 1);
    return 0;
}

// --------------------------------------------------------------------------
// SDL2 backend (opt-in – build without -DUSE_GLFW, use -s USE_SDL=2)
// --------------------------------------------------------------------------
#else // !USE_GLFW

static SDL_Window*   g_window = nullptr;
static SDL_GLContext g_glctx  = nullptr;

static void main_loop()
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT)
            emscripten_cancel_main_loop();
    }
    g_triangle.Render();
    SDL_GL_SwapWindow(g_window);
}

int main()
{
    LOGI("GLPI Framework Intro : WebGL / Emscripten (SDL2)");

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        LOGE("SDL_Init failed: %s", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    g_window = SDL_CreateWindow(
        "GLPI Framework Intro",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!g_window) { LOGE("SDL_CreateWindow failed: %s", SDL_GetError()); return -1; }

    g_glctx = SDL_GL_CreateContext(g_window);
    if (!g_glctx) { LOGE("SDL_GL_CreateContext failed: %s", SDL_GetError()); return -1; }

    g_triangle.InitModel();
    g_triangle.Resize(800, 600);

    emscripten_set_main_loop(main_loop, 0, 1);
    return 0;
}

#endif // USE_GLFW

// ==========================================================================
// Desktop – Windows / GLFW
// ==========================================================================
#elif defined(PLATFORM_WINDOWS)

#include <iostream>

static void framebufferSizeCB(GLFWwindow* /*win*/, int w, int h)
{
    g_triangle.Resize(w, h);
}

int main()
{
    std::cout << "GLPI Framework Intro - Desktop (GLFW)\n";
    std::cout << "Watch the triangle rotate. Press ESC to quit.\n";

    if (!glfwInit()) { std::cerr << "glfwInit failed\n"; return -1; }

#ifdef __APPLE__
    // macOS cannot create OpenGL ES contexts (no EGL); use a desktop GL core
    // profile instead. ShaderHelper retargets the GLES shaders to GLSL core.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE,        GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_CLIENT_API,            GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE,        GLFW_OPENGL_ANY_PROFILE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLPI Framework Intro", nullptr, nullptr);
    if (!window) {
        std::cerr << "glfwCreateWindow failed\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) { std::cerr << "glewInit failed\n"; return -1; }
#ifdef __APPLE__
    // Desktop core profiles have no default VAO (GLES 3.0 does) and ignore
    // gl_PointSize unless GL_PROGRAM_POINT_SIZE is enabled.
    GLuint defaultVAO = 0;
    glGenVertexArrays(1, &defaultVAO);
    glBindVertexArray(defaultVAO);
    glEnable(GL_PROGRAM_POINT_SIZE);
#endif

    glfwSetFramebufferSizeCallback(window, framebufferSizeCB);

    g_triangle.InitModel();
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    g_triangle.Resize(w, h);

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        g_triangle.Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

#endif // PLATFORM_WINDOWS
