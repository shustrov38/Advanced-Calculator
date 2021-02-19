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
        OpTree/tree.?)

add_executable(${CMAKE_PROJECT_NAME} main.c ${SOURCES})

set(CALC_TIMEOUT 1)

enable_testing()

if (BUILD_TESTING)
    add_test(ExampleTest ${CMAKE_PROJECT_NAME} "../input.txt")

    set_tests_properties(ExampleTest
            PROPERTIES TIMEOUT ${CALC_TIMEOUT})

    set_tests_properties(ExampleTest PROPERTIES
            PASS_REGULAR_EXPRESSION "a = 3.141593"
            FAIL_REGULAR_EXPRESSION "Error!")
endif ()
