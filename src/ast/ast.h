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

enum class UnaryOp
{
    NEGATE,
    ABS,
};

enum class BinaryOp
{
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE
};

struct UnaryExpr : Expr
{
    UnaryOp op;
    std::unique_ptr<Expr> expr;

    UnaryExpr(UnaryOp op, std::unique_ptr<Expr> expr)
        : op(op), expr(std::move(expr)) {}
};

struct BinaryExpr : Expr
{
    BinaryOp op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;

    BinaryExpr(BinaryOp op, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(op), left(std::move(l)), right(std::move(r)) {}
};
