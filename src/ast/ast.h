#include <memory>

struct Expr
{
    virtual ~Expr() = default;
};

struct NumberExpr : Expr
{
    int value;
    NumberExpr(int val) : value(val) {}
};

enum class BinaryOp
{
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE
};

struct BinaryExpr : Expr
{
    BinaryOp op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;

    BinaryExpr(BinaryOp oper, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(oper), left(std::move(l)), right(std::move(r)) {}
};
