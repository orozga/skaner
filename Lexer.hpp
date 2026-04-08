#pragma once

#include "Token.hpp"

class Lexer {
private:
    std::string expression;
    size_t pos;
    char curr;
    int row;
    int column;
    std::vector<Token> tokens;
public:
    Lexer(std::string source);
    void advance();
    Token getNumber();
    Token getIdentifierOrKeyword();
    Token getStringLiteral();
    Token getCharLiteral();
    Token getComment();
    Token getWhitespace();
    Token getNextToken();
    const std::vector<Token>& getTokens();
};
