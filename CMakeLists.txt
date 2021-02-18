cmake_minimum_required(VERSION 3.17)
project(Advanced_Calculator C)

set(CMAKE_C_STANDARD 11)

set(debug_var OFF)

if (debug_var)
    add_compile_definitions(__GRAPH_DEBUG__)
endif ()

add_executable(Advanced_Calculator main.c Stack/stack.c Stack/stack.h Operations/ops.c Operations/ops.h Parser/Parser.h Parser/Parser.c RPN/RPN.c RPN/RPN.h OpTree/tree.c OpTree/tree.h Graph/graph.c Graph/graph.h)
