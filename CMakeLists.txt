cmake_minimum_required(VERSION 3.17)
project(Advanced_Calculator C)

set(CMAKE_C_STANDARD 11)

set(DEBUG_VAR ON)

if (DEBUG_VAR)
#    add_compile_definitions(__PARSER_DEBUG__) # parser expression debug
#    add_compile_definitions(__GRAPH_DEBUG__ ) # print all graph data
#    add_compile_definitions(__RPN_DEBUG__   ) # debug info for RPN
#    add_compile_definitions(__EXP_DEBUG__   ) # print stack and builded tree
endif ()

file(GLOB SOURCES
        Stack/stack.?
        Operations/ops.?
        Operations/constructions.?
        Parser/parser.?
        Graph/graph.?
        RPN/RPN.?
        OpTree/tree.?)

enable_testing()

add_executable(${CMAKE_PROJECT_NAME} main.c ${SOURCES})

add_test(Power_operator             ${CMAKE_PROJECT_NAME} "../DataForTests/power_operations.txt"        )
add_test(Power_and_subtract         ${CMAKE_PROJECT_NAME} "../DataForTests/power_and_subs.txt"          )
add_test(More_subs                  ${CMAKE_PROJECT_NAME} "../DataForTests/more_subs.txt"               )
add_test(Bad_function_2_arguments   ${CMAKE_PROJECT_NAME} "../DataForTests/bad_function_2_args.txt"     )
add_test(Simple_unary_operations    ${CMAKE_PROJECT_NAME} "../DataForTests/simple_unary_operations.txt" )
add_test(Unary_operations           ${CMAKE_PROJECT_NAME} "../DataForTests/unary_operations.txt"        )
add_test(Complex_and_unary          ${CMAKE_PROJECT_NAME} "../DataForTests/complex_and_unary.txt"       )

add_test(Alex_test_1                ${CMAKE_PROJECT_NAME} "../DataForTests/alex_test1.txt"              )
add_test(Alex_test_2                ${CMAKE_PROJECT_NAME} "../DataForTests/alex_test2.txt"              )
add_test(Alex_test_3                ${CMAKE_PROJECT_NAME} "../DataForTests/alex_test3.txt"              )

add_test(Igor_test_1                ${CMAKE_PROJECT_NAME} "../DataForTests/igor_test1.txt"              )
add_test(Igor_test_2                ${CMAKE_PROJECT_NAME} "../DataForTests/igor_test2.txt"              )
add_test(Igor_test_3                ${CMAKE_PROJECT_NAME} "../DataForTests/igor_test3.txt"              )

add_test(Tim_test_1                 ${CMAKE_PROJECT_NAME} "../DataForTests/tim_test1.txt"               )
add_test(Tim_test_2                 ${CMAKE_PROJECT_NAME} "../DataForTests/tim_test2.txt"               )
add_test(Tim_test_3                 ${CMAKE_PROJECT_NAME} "../DataForTests/tim_test3.txt"               )

set_tests_properties(Power_operator             PROPERTIES PASS_REGULAR_EXPRESSION "res = 256"                  )
set_tests_properties(Power_and_subtract         PROPERTIES PASS_REGULAR_EXPRESSION "res = -256"                 )
set_tests_properties(More_subs                  PROPERTIES PASS_REGULAR_EXPRESSION "res = 13"                   )
set_tests_properties(Bad_function_2_arguments   PROPERTIES WILL_FAIL TRUE                                       )
set_tests_properties(Simple_unary_operations    PROPERTIES PASS_REGULAR_EXPRESSION "res = 190"                  )
set_tests_properties(Unary_operations           PROPERTIES PASS_REGULAR_EXPRESSION "res = -14.750000"           )
set_tests_properties(Complex_and_unary          PROPERTIES PASS_REGULAR_EXPRESSION "res = 30 - 3i"              )

set_tests_properties(Alex_test_1                PROPERTIES PASS_REGULAR_EXPRESSION "res = 31281265.366243"      )
set_tests_properties(Alex_test_2                PROPERTIES PASS_REGULAR_EXPRESSION "res = 34842.291976"         )
set_tests_properties(Alex_test_3                PROPERTIES PASS_REGULAR_EXPRESSION "res = 0.000170"             )

set_tests_properties(Igor_test_1                PROPERTIES PASS_REGULAR_EXPRESSION "res = 1.326028"             )
set_tests_properties(Igor_test_2                PROPERTIES PASS_REGULAR_EXPRESSION "res = 1.455010"             )
set_tests_properties(Igor_test_3                PROPERTIES PASS_REGULAR_EXPRESSION "res = 1.517427"             )

set_tests_properties(Tim_test_1                 PROPERTIES PASS_REGULAR_EXPRESSION "res = 24"                   )
set_tests_properties(Tim_test_2                 PROPERTIES PASS_REGULAR_EXPRESSION "res = 3971.500000"          )
set_tests_properties(Tim_test_3                 PROPERTIES PASS_REGULAR_EXPRESSION "res = 4"                    )