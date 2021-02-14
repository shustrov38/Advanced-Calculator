cmake_minimum_required(VERSION 3.17)
project(Advanced_Calculator C)

set(CMAKE_C_STANDARD 11)

add_executable(Advanced_Calculator main.c Stack/stack.c Stack/stack.h Operations/ops.c Operations/ops.h)