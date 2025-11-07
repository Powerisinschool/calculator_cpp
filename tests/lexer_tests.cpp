#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "../src/lexer/lexer.h"

TEST_CASE("Empty string tokenizes to EOF")
{
    Lexer lx("");
    Token t1 = lx.next();
    REQUIRE(t1.type == TokenType::EOF_TOKEN);
}

TEST_CASE("Single number tokenizes correctly")
{
    Lexer lx("42");
    Token t1 = lx.next();
    REQUIRE(t1.type == TokenType::NUMBER);
    REQUIRE(t1.value == 42);

    REQUIRE(lx.next().type == TokenType::EOF_TOKEN);
}

TEST_CASE("Whitespace is ignored")
{
    Lexer lx("   7   ");
    Token t1 = lx.next();
    // expect: NUMBER(7), EOF
    REQUIRE(t1.type == TokenType::NUMBER);
    REQUIRE(t1.value == 7);

    REQUIRE(lx.next().type == TokenType::EOF_TOKEN);
}

TEST_CASE("Multiple tokens in sequence")
{
    Lexer lx("3 + 5");
    Token t1 = lx.next();
    REQUIRE(t1.type == TokenType::NUMBER);
    REQUIRE(t1.value == 3);

    Token t2 = lx.next();
    REQUIRE(t2.type == TokenType::PLUS);

    Token t3 = lx.next();
    REQUIRE(t3.type == TokenType::NUMBER);
    REQUIRE(t3.value == 5);

    REQUIRE(lx.next().type == TokenType::EOF_TOKEN);
}

TEST_CASE("Operators tokenize correctly")
{
    Lexer lx("+ - * / ( )");
    Token t1 = lx.next();
    REQUIRE(t1.type == TokenType::PLUS);

    Token t2 = lx.next();
    REQUIRE(t2.type == TokenType::MINUS);

    Token t3 = lx.next();
    REQUIRE(t3.type == TokenType::STAR);

    Token t4 = lx.next();
    REQUIRE(t4.type == TokenType::SLASH);

    Token t5 = lx.next();
    REQUIRE(t5.type == TokenType::LPAREN);

    Token t6 = lx.next();
    REQUIRE(t6.type == TokenType::RPAREN);

    REQUIRE(lx.next().type == TokenType::EOF_TOKEN);
}

TEST_CASE("Expression without spaces tokenizes correctly")
{
    Lexer lx("2*3+4");
    Token t1 = lx.next();
    REQUIRE(t1.type == TokenType::NUMBER);
    REQUIRE(t1.value == 2);

    Token t2 = lx.next();
    REQUIRE(t2.type == TokenType::STAR);

    Token t3 = lx.next();
    REQUIRE(t3.type == TokenType::NUMBER);
    REQUIRE(t3.value == 3);

    Token t4 = lx.next();
    REQUIRE(t4.type == TokenType::PLUS);

    Token t5 = lx.next();
    REQUIRE(t5.type == TokenType::NUMBER);
    REQUIRE(t5.value == 4);

    REQUIRE(lx.next().type == TokenType::EOF_TOKEN);
}

TEST_CASE("Numbers may be multi-digit and decimal")
{
    Lexer lx("12.5");
    Token t1 = lx.next();
    REQUIRE(t1.type == TokenType::NUMBER);
    REQUIRE_THAT(t1.value, Catch::Matchers::WithinAbs(12.5, 1e-12));

    REQUIRE(lx.next().type == TokenType::EOF_TOKEN);
}

TEST_CASE("Invalid character tokenizes to INVALID")
{
    Lexer lx("@");
    Token t1 = lx.next();
    REQUIRE(t1.type == TokenType::INVALID);
}
