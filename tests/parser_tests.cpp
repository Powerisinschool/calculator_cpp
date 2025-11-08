#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "parser/parser.h"

TEST_CASE("Parses single number")
{
    Parser p("42");
    auto expr = p.parseExpression();

    auto num = dynamic_cast<NumberExpr *>(expr.get());

    REQUIRE_FALSE(num == nullptr);
    REQUIRE(num->value == 42);
}

TEST_CASE("Parses simple addition correctly")
{
    Parser p("1 + 2");
    auto expr = p.parseExpression();

    auto bin = dynamic_cast<BinaryExpr *>(expr.get());
    REQUIRE_FALSE(bin == nullptr);
    REQUIRE(bin->op == BinaryOp::PLUS);

    auto left = dynamic_cast<NumberExpr *>(bin->left.get());
    auto right = dynamic_cast<NumberExpr *>(bin->right.get());

    REQUIRE_FALSE(left == nullptr);
    REQUIRE_FALSE(right == nullptr);

    REQUIRE(left->value == 1);
    REQUIRE(right->value == 2);
}

TEST_CASE("Multiplies before addition")
{
    Parser p("1 + 2 * 5");
    auto expr = p.parseExpression();

    auto plus = dynamic_cast<BinaryExpr *>(expr.get());
    REQUIRE_FALSE(plus == nullptr);
    REQUIRE(plus->op == BinaryOp::PLUS);

    auto mult = dynamic_cast<BinaryExpr *>(plus->right.get());
    REQUIRE_FALSE(mult == nullptr);
    REQUIRE(mult->op == BinaryOp::MULTIPLY);

    p = Parser("1 * 2 + 5");
    expr = p.parseExpression();

    plus = dynamic_cast<BinaryExpr *>(expr.get());
    REQUIRE_FALSE(plus == nullptr);
    REQUIRE(plus->op == BinaryOp::PLUS);

    mult = dynamic_cast<BinaryExpr *>(plus->left.get());
    REQUIRE_FALSE(mult == nullptr);
    REQUIRE(mult->op == BinaryOp::MULTIPLY);
}

TEST_CASE("Parses parentheses correctly")
{
    Parser p("(1 + 2) * 3");
    auto expr = p.parseExpression();

    // (1 + 2) * 3  →  multiply(left = plus(1,2), right = 3)

    auto mult = dynamic_cast<BinaryExpr *>(expr.get());
    REQUIRE(mult != nullptr);
    REQUIRE(mult->op == BinaryOp::MULTIPLY);

    auto plus = dynamic_cast<BinaryExpr *>(mult->left.get());
    REQUIRE(plus != nullptr);
    REQUIRE(plus->op == BinaryOp::PLUS);

    auto left = dynamic_cast<NumberExpr *>(plus->left.get());
    auto right = dynamic_cast<NumberExpr *>(plus->right.get());
    REQUIRE(left != nullptr);
    REQUIRE(right != nullptr);
    REQUIRE(left->value == 1);
    REQUIRE(right->value == 2);

    auto last = dynamic_cast<NumberExpr *>(mult->right.get());
    REQUIRE(last != nullptr);
    REQUIRE(last->value == 3);
}

TEST_CASE("Parses unary minus")
{
    Parser p("-5 + 3");
    auto expr = p.parseExpression();

    auto plus = dynamic_cast<BinaryExpr *>(expr.get());
    REQUIRE(plus != nullptr);
    REQUIRE(plus->op == BinaryOp::PLUS);

    auto left = dynamic_cast<UnaryExpr *>(plus->left.get());
    REQUIRE(left != nullptr);
    REQUIRE(left->op == UnaryOp::NEGATE);

    auto num = dynamic_cast<NumberExpr *>(left->expr.get());
    REQUIRE(num != nullptr);
    REQUIRE(num->value == 5);

    auto right = dynamic_cast<NumberExpr *>(plus->right.get());
    REQUIRE(right != nullptr);
    REQUIRE(right->value == 3);
}

TEST_CASE("Parses absolute expression")
{
    Parser p("|5 + 3|");
    auto expr = p.parseExpression();

    auto abs = dynamic_cast<UnaryExpr *>(expr.get());
    REQUIRE(abs != nullptr);
    REQUIRE(abs->op == UnaryOp::ABS);

    auto plus = dynamic_cast<BinaryExpr *>(abs->expr.get());
    REQUIRE(plus != nullptr);
    REQUIRE(plus->op == BinaryOp::PLUS);

    auto left = dynamic_cast<NumberExpr *>(plus->left.get());
    auto right = dynamic_cast<NumberExpr *>(plus->right.get());
    REQUIRE(left != nullptr);
    REQUIRE(right != nullptr);
    REQUIRE(left->value == 5);
    REQUIRE(right->value == 3);
}

TEST_CASE("Parses absolute single number")
{
    Parser p("|-7|");
    auto expr = p.parseExpression();

    auto abs = dynamic_cast<UnaryExpr *>(expr.get());
    REQUIRE(abs != nullptr);
    REQUIRE(abs->op == UnaryOp::ABS);

    auto e = dynamic_cast<UnaryExpr *>(abs->expr.get());
    REQUIRE(e != nullptr);
    REQUIRE(e->op == UnaryOp::NEGATE);

    auto num = dynamic_cast<NumberExpr *>(e->expr.get());
    REQUIRE(num != nullptr);
    REQUIRE(num->value == 7);
}
