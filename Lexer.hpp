#pragma once

#include "Token.hpp"

class Lexer {
private:
    std::string expression;
    size_t pos;
    char curr;
    int column;
public:
    Lexer(std::string source);
    void advance();
    void skipWhiteSpace();
    Token getNumber();
    Token getId();
    Token getNextToken();
};
