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
            case TokenType::INT:            typeName = "INT(" + value + ")"; break; //0
            case TokenType::ID:             typeName = "ID"; break; //1
            case TokenType::PLUS:           typeName = "PLUS"; break; //2
            case TokenType::MINUS:          typeName = "MINUS"; break; //3
            case TokenType::MULTIPLY:       typeName = "MULTIPLY"; break; //4
            case TokenType::DIVIDE:         typeName = "DIVIDE"; break; //5
            case TokenType::LPAREN:         typeName = "LPAREN"; break; //6
            case TokenType::RPAREN:         typeName = "RPAREN"; break; //7
            case TokenType::ERROR:          typeName = "ERROR"; break; //9
            case TokenType::EOF_TOKEN:      typeName = "EOF"; break; //8
            default:                        typeName = "UNKNOWN"; break;
        }
        return "(" + typeName + ", '" + value + "') [kolumna: " + std::to_string(column) + "]";
    }
};