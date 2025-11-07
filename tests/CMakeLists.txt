enable_testing()

add_executable(calc_tests
    catch_amalgamated.cpp
    lexer_tests.cpp
    # parser_tests.cpp
    # ast_tests.cpp
    # evaluator_tests.cpp
)

target_link_libraries(calc_tests PRIVATE calc_core)

add_test(NAME CalcTests COMMAND calc_tests)
