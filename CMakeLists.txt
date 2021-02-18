cmake_minimum_required(VERSION 3.17)
project(Advanced_Calculator C)

set(CMAKE_C_STANDARD 11)

set(DEBUG_VAR OFF)

if (DEBUG_VAR)
    add_compile_definitions(__GRAPH_DEBUG__)
endif ()

file(GLOB SOURCES
    Stack/stack.?
    Operations/ops.?
    Parser/Parser.?
    Graph/graph.?
    RPN/RPN.?
    OpTree/tree.?
)

add_executable(Advanced_Calculator main.c ${SOURCES})
