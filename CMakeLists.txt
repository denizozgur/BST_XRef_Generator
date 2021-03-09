cmake_minimum_required(VERSION 3.17)
project(C_HW5 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(C_HW5
		leader.c
		part_A.c
		part_B.c
		team.h)
