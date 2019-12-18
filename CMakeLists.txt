cmake_minimum_required(VERSION 3.15)
project(ui_workflow LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SHARED_LIBRARY_PREFIX "libantara")
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message(STATUS "ui as shared")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}_nim)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}_nim)


include(FetchContent)
FetchContent_Declare(imgui
        URL https://github.com/rokups/imgui/archive/hdpi-support.zip)
FetchContent_MakeAvailable(imgui)
find_package(glad CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_library(ui_workflow)
target_sources(ui_workflow PRIVATE
        ui_wrapper.h
        ui.wrapper.hpp
        ui.wrapper.cpp
        ui_wrapper.cpp
        private/cimgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/examples/imgui_impl_sdl.cpp
        ${imgui_SOURCE_DIR}/examples/imgui_impl_opengl3.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui.cpp
        $<$<PLATFORM_ID:Darwin>:${imgui_SOURCE_DIR}/examples/imgui_impl_osx.mm>
        $<$<PLATFORM_ID:Windows>:${imgui_SOURCE_DIR}/examples/imgui_impl_win32.cpp>)
if (WIN32)
    set_property(TARGET ui_workflow PROPERTY
            MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif()
target_include_directories(ui_workflow PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/examples/ ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(ui_workflow PRIVATE cxx_std_17)
target_link_libraries(ui_workflow
        PRIVATE
        $<$<PLATFORM_ID:Darwin>:SDL2::SDL2-static>
        $<$<PLATFORM_ID:Linux>:SDL2::SDL2-static>
        $<$<PLATFORM_ID:Windows>:SDL2::SDL2-static>
        #SDL2::SDL2main
        glad::glad)

add_executable(ui_example main.c)
target_link_libraries(ui_example PUBLIC ui_workflow)

add_executable(ui_example_cpp main.cpp)
target_link_libraries(ui_example_cpp PUBLIC ui_workflow)

include(GNUInstallDirs)

install(FILES ui_wrapper.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES private/cimgui.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS ui_workflow EXPORT UiWorkflow
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})