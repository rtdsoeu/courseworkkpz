cmake_minimum_required(VERSION 3.23)
project(coursework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
add_library(imgui STATIC)
target_include_directories(imgui
    PUBLIC ${IMGUI_DIR}
    PUBLIC ${IMGUI_DIR}/backends
)
target_sources(imgui PRIVATE
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp

        ${IMGUI_DIR}/backends/imgui_impl_dx11.cpp
        ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
)

add_compile_definitions(UNICODE _UNICODE)
if (MSVC)
    add_compile_options(/utf-8)
endif()
add_executable(${PROJECT_NAME} WIN32 main.cpp imwindows/imwindows.cpp imguiaddons/imguidatechooser.cpp requests/amount_masters.hpp resources/application_icon.rc)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)
