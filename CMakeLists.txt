cmake_minimum_required(VERSION 3.10)
project(skaner)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(skaner
        Lexer.cpp
        Lexer.hpp
        HtmlRenderer.cpp
        HtmlRenderer.hpp
        main.cpp
        Token.hpp)