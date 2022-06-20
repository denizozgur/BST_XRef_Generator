cmake_minimum_required(VERSION 3.16)
project(BST_XRef_Generator C)
set(CMAKE_C_STANDARD 11)
add_executable(BST_XRef_Generator BST.h BST.c main.c)
