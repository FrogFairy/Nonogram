cmake_minimum_required(VERSION 3.20)
project(nonogram)

set(CMAKE_CXX_STANDARD 17)

set(FLTK_ROOT "C:/Program Files (x86)/FLTK/bin")
find_package(FLTK REQUIRED)

set(TARGET "nonogram")
add_executable(
    ${TARGET} 
    src/main.cpp
    src/database.cpp
    src/create_level.cpp


    src/main_window.cpp
    src/generate_level.cpp
    src/choose_level.cpp
    src/play_window.cpp
    src/rules_window.cpp
    src/wrapper.cpp

    src/logic_board.cpp
    src/graph_board.cpp
    src/buttons.cpp

    src/Graph_lib/Graph.cpp
    src/Graph_lib/GUI.cpp
    src/Graph_lib/Window.cpp
    src/sqlite3/sqlite3.c
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