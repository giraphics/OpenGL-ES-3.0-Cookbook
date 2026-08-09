#define LOG_TAG "Triangle"

#include "Triangle.h"
#include <cmath>
#include <string>

// ---------------------------------------------------------------------------
// Vertex data
// ---------------------------------------------------------------------------

static const GLfloat kPositions[] = {
     0.0f,  0.5f,
    -0.5f, -0.5f,
     0.5f, -0.5f
};

static const GLfloat kColors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

// ---------------------------------------------------------------------------
// Shaders
// ---------------------------------------------------------------------------

static const char kVertexShader[] =
    "#version 300 es                                           \n"
    "layout(location = 0) in vec4 VertexPosition;             \n"
    "layout(location = 1) in vec3 VertexColor;                \n"
    "uniform float RadianAngle;                                \n"
    "out vec4 TriangleColor;                                   \n"
    "void main() {                                             \n"
    "  mat2 r = mat2(cos(RadianAngle),  sin(RadianAngle),      \n"
    "               -sin(RadianAngle),  cos(RadianAngle));     \n"
    "  vec2 pos = r * VertexPosition.xy;                       \n"
    "  gl_Position = vec4(pos, 0.0, 1.0);                      \n"
    "  TriangleColor = vec4(VertexColor, 1.0);                 \n"
    "}\n";

static const char kFragmentShader[] =
    "#version 300 es            \n"
    "precision mediump float;   \n"
    "in  vec4 TriangleColor;    \n"
    "out vec4 FragColor;        \n"
    "void main() {              \n"
    "  FragColor = TriangleColor;\n"
    "}";

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static GLuint compileShader(GLenum type, const char* src)
{
#ifdef __APPLE__
    // macOS has no OpenGL ES; the context is desktop GL core, so the
    // GLES version line must be retargeted before compiling.
    std::string patched(src);
    const std::string esVersion("#version 300 es");
    size_t pos = patched.find(esVersion);
    if (pos != std::string::npos)
        patched.replace(pos, esVersion.size(), "#version 330 core");
    src = patched.c_str();
#endif
    GLuint shader = glCreateShader(type);
    if (!shader) { LOGE("glCreateShader failed (type=0x%x)", type); return 0; }
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    GLint ok = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        std::string log(static_cast<size_t>(len), '\0');
        glGetShaderInfoLog(shader, len, nullptr, &log[0]);
        LOGE("Shader compile error:\n%s", log.c_str());
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static GLuint createProgram(const char* vertSrc, const char* fragSrc)
{
    GLuint vs = compileShader(GL_VERTEX_SHADER,   vertSrc);
    if (!vs) return 0;
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragSrc);
    if (!fs) { glDeleteShader(vs); return 0; }

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    GLint ok = GL_FALSE;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
        std::string log(static_cast<size_t>(len), '\0');
        glGetProgramInfoLog(prog, len, nullptr, &log[0]);
        LOGE("Program link error:\n%s", log.c_str());
        glDeleteProgram(prog);
        prog = 0;
    }
    glDetachShader(prog, vs);
    glDetachShader(prog, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

// ---------------------------------------------------------------------------
// Triangle
// ---------------------------------------------------------------------------

Triangle::Triangle()  = default;

Triangle::~Triangle()
{
    glDeleteBuffers(1, &vboColor);
    glDeleteBuffers(1, &vboPos);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(programID);
}

void Triangle::InitModel()
{
    LOGI("Triangle::InitModel");

    programID = createProgram(kVertexShader, kFragmentShader);
    if (!programID) { LOGE("Triangle: could not create program"); return; }

    uRadianAngle = glGetUniformLocation(programID, "RadianAngle");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vboPos);
    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kPositions), kPositions, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &vboColor);
    glBindBuffer(GL_ARRAY_BUFFER, vboColor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kColors), kColors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    LOGI("Triangle::InitModel done");
}

void Triangle::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programID);

    float radian = degree++ / 57.2957795f;
    glUniform1f(uRadianAngle, radian);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Triangle::Resize(int w, int h)
{
    glViewport(0, 0, w, h);
}
