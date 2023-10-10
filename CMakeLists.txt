cmake_minimum_required(VERSION 3.26)
project(spinning_image_cli C)

set(CMAKE_C_STANDARD 11)

add_executable(spinning_image_cli main.c
        point.h
        matrix.h
        mafs.h
        point.c
        mafs.c
        matrix.c)
