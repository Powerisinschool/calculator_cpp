#include <string>

// This defines the type given to the token
// note that 'SPACE' characters will be ignored, and not 'INVALID'
// all other unrecognized symbols will be assigned as 'INVALID'
enum TokenType
{
    NUMBER,
    PLUS,      // '+'
    MINUS,     // '-'
    STAR,      // '*'
    SLASH,     // '/'
    LPAREN,    // '('
    RPAREN,    // ')'
    EOF_TOKEN, // 'EOF'
    INVALID,   // optional, error handling
};

struct Token
{
    TokenType type;
    std::string lexeme; // raw substring
    double value;       // for 'number' type
};

class Lexer
{
public:
    explicit Lexer(const std::string &input);
    ~Lexer();

    Token next();       // return next and advance
    Token peek() const; // inspect next token without advancing
};
