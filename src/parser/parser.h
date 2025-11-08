#include <memory>
#include <string>
#include <vector>
#include "lexer/lexer.h"
#include "ast/ast.h"

class Parser
{
public:
    explicit Parser(const std::string &input);

    std::unique_ptr<Expr> parseExpression();

private:
    size_t current_ = 0;
    std::vector<Token> tokens;

    std::unique_ptr<Expr> parseFactor();
    std::unique_ptr<Expr> parseTerm();
    const Token &peek() const;
    const Token &advance();
    bool match(TokenType t);
};
