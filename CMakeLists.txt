cmake_minimum_required(VERSION 3.26)
project(CFluff C)

set(CMAKE_C_STANDARD 11)

add_executable(cfi main.c
        jlog.c
        jlog.h
)
