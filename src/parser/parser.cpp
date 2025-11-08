#include "parser.h"

Parser::Parser(const std::string &input)
{
    Lexer lx(input);
    Token token = lx.next();
    while (token.type != TokenType::EOF_TOKEN)
    {
        tokens.push_back(token);
        token = lx.next();
    }
};

std::unique_ptr<Expr> Parser::parseExpression()
{
    auto left = parseTerm();

    while (match(TokenType::PLUS) || match(TokenType::MINUS))
    {
        Token op = tokens[current_ - 1];
        auto right = parseTerm();

        BinaryOp binOp = (op.type == TokenType::PLUS) ? BinaryOp::PLUS : BinaryOp::MINUS;

        left = std::make_unique<BinaryExpr>(binOp, std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<Expr> Parser::parseTerm()
{
    auto left = parseFactor();

    while (match(TokenType::STAR) || match(TokenType::SLASH))
    {
        Token op = tokens[current_ - 1];
        auto right = parseFactor();

        BinaryOp binOp = (op.type == TokenType::STAR) ? BinaryOp::MULTIPLY : BinaryOp::DIVIDE;
        left = std::make_unique<BinaryExpr>(binOp, std::move(left), std::move(right));
    }

    return left;
    // TODO: handle exponentiation on a separate level if needed
}

std::unique_ptr<Expr> Parser::parseFactor()
{
    // Unary minus
    if (match(TokenType::MINUS))
    {
        auto expr = parseFactor();
        return std::make_unique<UnaryExpr>(UnaryOp::NEGATE, std::move(expr));
    }

    // Absolute operation
    if (match(TokenType::ABS))
    {
        auto expr = parseExpression();
        if (!match(TokenType::ABS))
        {
            throw std::runtime_error("Expected closing abs, '|'");
        }
        return std::make_unique<UnaryExpr>(UnaryOp::ABS, std::move(expr));
    }

    // Parenthesized expression: (expr)
    if (match(TokenType::LPAREN))
    {
        auto expr = parseExpression();
        if (!match(TokenType::RPAREN))
        {
            throw std::runtime_error("Expected closing bracket, ')");
        }
        return expr;
    }

    // Number
    if (peek().type == TokenType::NUMBER)
    {
        int value = peek().value;
        advance();
        return std::make_unique<NumberExpr>(value);
    }

    return nullptr;
}

const Token &Parser::peek() const
{
    return tokens[current_];
}

const Token &Parser::advance()
{
    return tokens[current_++];
}

bool Parser::match(TokenType t)
{
    if (peek().type == t)
    {
        advance(); // consume token
        return true;
    }
    return false;
}
