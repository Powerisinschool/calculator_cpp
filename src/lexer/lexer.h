struct Token
{
    //
};

class Lexer
{
public:
    Lexer();
    ~Lexer();

    Token next();       // return next and advance
    Token peek() const; // inspect next token without advancing
};
