#include <string>

struct Token
{
    //
};

class Lexer
{
public:
    Lexer(const std::string &input);
    ~Lexer();

    Token next();       // return next and advance
    Token peek() const; // inspect next token without advancing
};
