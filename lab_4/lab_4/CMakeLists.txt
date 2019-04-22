cmake_minimum_required(VERSION 3.13)
project(lab_4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(lab_4
        extmem.c extmem.h test.c random_data.c random_data.h)
