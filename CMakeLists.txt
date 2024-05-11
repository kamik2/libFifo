cmake_minimum_required(VERSION 3.26)
project(libFifo C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(libFifo
        Src/fifo.c
        Src/fifo.h
)
