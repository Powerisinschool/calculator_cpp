file(GLOB SRC_LEXER lexer/*.cpp lexer/*.h)
file(GLOB SRC_PARSER parser/*.cpp parser/*.h)
file(GLOB SRC_AST ast/*.cpp ast/*.h)
file(GLOB SRC_EVAL evaluator/*.cpp evaluator/*.h)

add_library(calc_core
    ${SRC_LEXER}
    ${SRC_PARSER}
    ${SRC_AST}
    ${SRC_EVAL}
)

target_include_directories(calc_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(calc main.cpp)
target_link_libraries(calc PRIVATE calc_core)
