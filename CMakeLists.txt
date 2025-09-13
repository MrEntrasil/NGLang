cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES
    main.cpp
    frontend/Lexer.cpp
)

project(nglang LANGUAGES CXX)
add_executable(nglang ${SOURCES})