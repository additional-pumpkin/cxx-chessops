cmake_minimum_required(VERSION 3.16)
project(chessops LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wno-deprecated-enum-enum-conversion")


add_subdirectory(src)


add_executable(chessops-test examples/main.cxx)

target_link_libraries(chessops-test chessops)
target_include_directories(chessops-test PRIVATE src)