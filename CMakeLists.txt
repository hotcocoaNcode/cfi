cmake_minimum_required(VERSION 3.26)
project(CFluff C)

add_compile_options(-O2)

set(CMAKE_C_STANDARD 11)

add_executable(cfi main.c jlog.c jlog.h
        interpretModes.c
        interpretModes.h)