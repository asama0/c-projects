#change this if you happen to be working with a lower version of CMake
cmake_minimum_required(VERSION 2.8)

project(chatbotproj)

#change this to Release to activate optimization and compile without debug symbols
set(CMAKE_BUILD_TYPE Debug)

#adds arbitrary flags to the compiler.
#this one is used to generate the files we give in input to Egypt.
set(CMAKE_C_FLAGS "-std=c99 -fdump-rtl-expand")

#creates an executable by compiling and linking a list of space separated C files.
add_executable(chatbot main.c )

