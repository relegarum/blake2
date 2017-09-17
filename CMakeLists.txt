cmake_minimum_required(VERSION 3.9.1)

project(blake)

if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-std=c++14 -Wall -Wextra -Wpedantic)
endif()

add_executable(blake blake_tests.cpp blake.c)
