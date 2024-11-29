cmake_minimum_required(VERSION 3.20)

project(Nonogram LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#add_compile_options(-Wall -Wextra)

set(FLTK_ROOT "C:/Program Files (x86)/FLTK/bin")
find_package(FLTK REQUIRED)

set(TARGET "Nonogram_project")

add_executable(
    ${TARGET}
    src/main.cpp
    src/wrapper.cpp
    src/create_level.cpp
    src/main_window.cpp
    src/generate_level.cpp
    src/choose_level.cpp
    src/Graph_lib/Graph.cpp
    src/Graph_lib/GUI.cpp
    src/Graph_lib/Window.cpp
)

target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${FLTK_INCLUDE_DIR}
)

target_link_directories(${TARGET} PRIVATE
    ${FLTK_INCLUDE_DIR}/../lib
)

target_link_libraries(${TARGET} PRIVATE 
    ${FLTK_LIBRARIES}
    fltk_jpeg
    fltk_png
    fltk_z
)

add_custom_target(CopyResources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resources
    ${CMAKE_BINARY_DIR}/resources
    COMMENT "Copying resources into runtime output directory"
)

add_dependencies(${TARGET} CopyResources)