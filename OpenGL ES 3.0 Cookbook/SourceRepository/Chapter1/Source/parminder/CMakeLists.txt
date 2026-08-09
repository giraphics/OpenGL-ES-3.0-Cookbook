# ===========================================================================
# CMakeLists.txt – Desktop (Windows) build for GLPIFrameworkIntro-Modern
#
# Scene/ holds: main.cpp (entry point), Triangle.cpp/.h (self-contained renderer),
#               Platform.h (GL + windowing headers).
# The same Triangle logic is mirrored as a monolithic JNI file for Android:
#   android/app/src/main/cpp/NativeTemplate.cpp
#
# Usage:
#   cmake -S . -B build_desktop -G "Visual Studio 17 2022" -A x64
#   cmake --build build_desktop --config Debug
# ===========================================================================

cmake_minimum_required(VERSION 3.15)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
cmake_policy(VERSION 3.15)

project(GLPIFrameworkIntro)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ImportDependencies)
importDependencies()

add_definitions(-DPLATFORM_WINDOWS -DGLEW_STATIC)

set(SCENE_DIR ${CMAKE_CURRENT_LIST_DIR}/Scene)
# Triangle.cpp + main.cpp — no other .cpp files remain in Scene/.
file(GLOB SCENE_SRC "${SCENE_DIR}/*.cpp")

add_executable(GLPIFrameworkIntro ${SCENE_SRC})

target_include_directories(GLPIFrameworkIntro PRIVATE ${SCENE_DIR})

target_link_libraries(GLPIFrameworkIntro
    PRIVATE glfw
    PRIVATE libglew_static
)

if(MSVC)
    target_compile_options(GLPIFrameworkIntro PRIVATE /W4 /WX- /permissive- /std:c++17)
endif()

add_custom_command(TARGET GLPIFrameworkIntro POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_LIST_DIR}/android/app/src/main/assets"
        "$<TARGET_FILE_DIR:GLPIFrameworkIntro>/assets"
    COMMENT "Copying shader assets to build directory"
)

# Tell Visual Studio to use the exe's output directory as the working
# directory when debugging, so the relative "assets/shader/" paths work.
set_target_properties(GLPIFrameworkIntro PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:GLPIFrameworkIntro>"
)
