cmake_minimum_required(VERSION 3.22.1)

project("glpiframeworkintro")

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT ANDROID)
    message(FATAL_ERROR "This CMakeLists.txt is for Android builds only.")
endif()

add_definitions(-DANDROID -DPLATFORM_ANDROID)

set(SCENE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Scene)

add_library(glpiframeworkintro SHARED
    NativeTemplate.cpp
    ${SCENE_DIR}/Triangle.cpp
)

target_include_directories(glpiframeworkintro PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SCENE_DIR}
)

find_library(log-lib     log)
find_library(android-lib android)
find_library(glesv3-lib  GLESv3)
find_library(egl-lib     EGL)

target_link_libraries(glpiframeworkintro
    ${log-lib}
    ${android-lib}
    ${glesv3-lib}
    ${egl-lib}
)
