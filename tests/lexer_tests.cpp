#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "../src/lexer/lexer.h"

TEST_CASE("Single number tokenizes correctly")
{
    Lexer lx("42");
    Token t1 = lx.next();
    REQUIRE(t1.type == TokenType::NUMBER);
    REQUIRE(t1.value == 42);

    Token t2 = lx.next();
    REQUIRE(t1.type == TokenType::EOF_TOKEN);
}
