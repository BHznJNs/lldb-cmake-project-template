cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_EXPORT_COMPILECOMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-18" )
set(CMAKE_CXX_STANDARD 17)

project(project_name VERSION 0.1.0 LANGUAGES CXX)

include_directories(include)

add_executable(main src/main.cpp)
