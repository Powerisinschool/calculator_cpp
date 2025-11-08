#include "lexer.h"
#include <stdexcept>
#include <cctype>

Lexer::Lexer(const std::string &input)
{
    source_ = input;
    position_ = 0;
}

Lexer::~Lexer()
{
    source_.clear();
    position_ = 0;
    source_.shrink_to_fit();
}

Token Lexer::next()
{
    skipWhitespace();

    // Check for End of File
    if (position_ >= source_.length())
    {
        return {EOF_TOKEN, "", 0};
    }

    char currentChar = source_[position_];

    switch (currentChar)
    {
    case '+':
        position_++;
        return {PLUS, "+", 0};
    case '-':
        position_++;
        return {MINUS, "-", 0};
    case '*':
        position_++;
        return {STAR, "*", 0};
    case '/':
        position_++;
        return {SLASH, "/", 0};
    case '(':
        position_++;
        return {LPAREN, "(", 0};
    case ')':
        position_++;
        return {RPAREN, ")", 0};
    case '|':
        position_++;
        return {ABS, "|", 0};
    default:
        if (std::isdigit(currentChar))
        {
            return readNumber();
        }
        else
        {
            return {INVALID, std::string(1, currentChar), 0};
        }
    }
}

Token Lexer::peek() const
{
    Token tmp;
    return tmp;
    // peek implementation here
}

void Lexer::skipWhitespace()
{
    while (position_ < source_.length() && std::isspace(source_[position_]))
    {
        position_++;
    }
}

Token Lexer::readNumber()
{
    size_t start = position_;
    while (position_ < source_.length() && (std::isdigit(source_[position_]) || source_[position_] == '.'))
    {
        position_++;
    }
    const std::string value = source_.substr(start, position_ - start);
    try
    {
        return {NUMBER, value, std::stod(value)};
    }
    catch (const std::invalid_argument &e)
    {
        return {INVALID, value, 0};
    }
    catch (const std::out_of_range &e)
    {
        return {INVALID, value, 0}; // TODO: handle out of range numbers
    }
}
