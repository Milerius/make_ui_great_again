cmake_minimum_required(VERSION 3.15)
project(ui_workflow LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(imgui
        URL https://github.com/rokups/imgui/archive/hdpi-support.zip)
FetchContent_MakeAvailable(imgui)
find_package(glad CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_library(ui_workflow)
target_sources(ui_workflow PUBLIC
        ui.wrapper.cpp
        ui_wrapper.cpp
        PUBLIC
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/examples/imgui_impl_sdl.cpp
        ${imgui_SOURCE_DIR}/examples/imgui_impl_opengl3.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui.cpp
        $<$<PLATFORM_ID:Darwin>:${imgui_SOURCE_DIR}/examples/imgui_impl_osx.mm>
        $<$<PLATFORM_ID:Windows>:${imgui_SOURCE_DIR}/examples/imgui_impl_win32.cpp>)
target_include_directories(ui_workflow PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/examples/)
target_compile_features(ui_workflow PRIVATE cxx_std_17)
target_link_libraries(ui_workflow PUBLIC
        glad::glad
        SDL2::SDL2main
        $<$<PLATFORM_ID:Darwin>:SDL2::SDL2-static>
        $<$<PLATFORM_ID:Linux>:SDL2::SDL2-static>
        $<$<PLATFORM_ID:Windows>:SDL2::SDL2>)

add_executable(ui_example main.c)
target_link_libraries(ui_example PUBLIC ui_workflow)

add_executable(ui_example_cpp main.cpp)
target_link_libraries(ui_example_cpp PUBLIC ui_workflow)