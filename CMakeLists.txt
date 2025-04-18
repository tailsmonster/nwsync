cmake_minimum_required(VERSION 3.10)
project(nwsync)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(nwsync
    src/main.cpp
    src/hex_reader.cpp
    src/files_utils.cpp
)