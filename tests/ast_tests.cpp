#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "ast/ast.h"

TEST_CASE("Number node holds correct value")
{
    NumberExpr numNode(42);
    REQUIRE(numNode.value == 42);
}

TEST_CASE("Binary expression node holds correct operator and operands")
{
    auto left = new NumberExpr(3);
    auto right = new NumberExpr(5);

    // BinaryExpr expr(BinaryOp::PLUS, left, right);
    auto expr = std::make_unique<BinaryExpr>(
        BinaryOp::PLUS,
        std::unique_ptr<NumberExpr>(left),
        std::unique_ptr<NumberExpr>(right));

    REQUIRE(expr->op == BinaryOp::PLUS);
    REQUIRE(dynamic_cast<NumberExpr *>(expr->left.get())->value == 3);
    REQUIRE(dynamic_cast<NumberExpr *>(expr->right.get())->value == 5);
}
