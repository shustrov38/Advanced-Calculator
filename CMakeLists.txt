cmake_minimum_required(VERSION 3.17)
project(Advanced_Calculator C)

set(CMAKE_C_STANDARD 11)

#set(DEBUG_VAR OFF)
#
#if (DEBUG_VAR)
#    add_compile_definitions(__GRAPH_DEBUG__)
#endif ()

file(GLOB SOURCES
        Stack/stack.?
        Operations/ops.?
        Parser/Parser.?
        Graph/graph.?
        RPN/RPN.?
        OpTree/tree.?)

enable_testing()

add_executable(${CMAKE_PROJECT_NAME} main.c ${SOURCES})


add_test(Power_operator ${CMAKE_PROJECT_NAME} "../DataForTests/power.txt")
add_test(Power_and_subtract ${CMAKE_PROJECT_NAME} "../DataForTests/power_and_subtraction.txt")
add_test(More_subs ${CMAKE_PROJECT_NAME} "../DataForTests/more_subs.txt")
add_test(Bad_function_2_arguments ${CMAKE_PROJECT_NAME} "../DataForTests/bad_function_2_args.txt")


set_tests_properties(Power_operator PROPERTIES PASS_REGULAR_EXPRESSION "res = 256")

set_tests_properties(Power_and_subtract PROPERTIES PASS_REGULAR_EXPRESSION "res = -256")

set_tests_properties(More_subs PROPERTIES PASS_REGULAR_EXPRESSION "res = 13")

set_tests_properties(Bad_function_2_arguments PROPERTIES WILL_FAIL TRUE)
