#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

enum class TokenType {
    INT,
    ID,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    EOF_TOKEN,
    ERROR
};

struct Token {
    TokenType type;
    std::string value;
    int column;

    Token(TokenType t, std::string v, int col) { type = t; value = v; column = col; }
    Token() = default;

    std::string toString() const {
        std::string typeName;
        switch (type) {
            case TokenType::INT:            typeName = "INT(" + value + ")"; break;
            case TokenType::ID:             typeName = "ID"; break;
            case TokenType::PLUS:           typeName = "PLUS"; break;
            case TokenType::MINUS:          typeName = "MINUS"; break;
            case TokenType::MULTIPLY:       typeName = "MULTIPLY"; break;
            case TokenType::DIVIDE:         typeName = "DIVIDE"; break;
            case TokenType::LPAREN:         typeName = "LPAREN"; break;
            case TokenType::RPAREN:         typeName = "RPAREN"; break;
            default:                        typeName = "UNKNOWN"; break;
        }
        return "(" + typeName + ", '" + value + "') [kolumna: " + std::to_string(column) + "]";
    }
};