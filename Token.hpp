#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

enum class TokenType {
    // Literals
    INT_LITERAL,
    STRING_LITERAL,
    CHAR_LITERAL,

    // Identifiers and keywords
    IDENTIFIER,
    KEYWORD,

    // Arithmetic operators
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,
    INCREMENT,
    DECREMENT,

    // Assignment and comparison
    ASSIGN,
    EQUAL,
    NOT_EQUAL,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,

    // Logical operators
    LOGICAL_AND,
    LOGICAL_OR,
    NOT,

    // Punctuation
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    LBRACKET,
    RBRACKET,
    SEMICOLON,
    COMMA,
    DOT,

    // Comments / Whitespace
    COMMENT,
    WHITESPACE,

    EOF_TOKEN,
    ERROR,

    // Compatibility aliases
    INT = INT_LITERAL,
    ID = IDENTIFIER
};

struct Token {
    TokenType type;
    std::string value;
    int column;

    Token(TokenType t, std::string v, int col)
        : type(t), value(std::move(v)), column(col) {}
    Token() = default;

    std::string toString() const {
        std::string typeName;
        switch (type) {
            case TokenType::INT_LITERAL:    typeName = "INT_LITERAL(" + value + ")"; break;
            case TokenType::STRING_LITERAL: typeName = "STRING_LITERAL(" + value + ")"; break;
            case TokenType::CHAR_LITERAL:   typeName = "CHAR_LITERAL('" + value + "')"; break;
            case TokenType::IDENTIFIER:     typeName = "IDENTIFIER(" + value + ")"; break;
            case TokenType::KEYWORD:        typeName = "KEYWORD(" + value + ")"; break;
            case TokenType::PLUS:           typeName = "PLUS"; break;
            case TokenType::MINUS:          typeName = "MINUS"; break;
            case TokenType::MULTIPLY:       typeName = "MULTIPLY"; break;
            case TokenType::DIVIDE:         typeName = "DIVIDE"; break;
            case TokenType::MODULO:         typeName = "MODULO"; break;
            case TokenType::INCREMENT:      typeName = "INCREMENT"; break;
            case TokenType::DECREMENT:      typeName = "DECREMENT"; break;
            case TokenType::ASSIGN:         typeName = "ASSIGN"; break;
            case TokenType::EQUAL:          typeName = "EQUAL"; break;
            case TokenType::NOT_EQUAL:      typeName = "NOT_EQUAL"; break;
            case TokenType::LESS:           typeName = "LESS"; break;
            case TokenType::LESS_EQUAL:     typeName = "LESS_EQUAL"; break;
            case TokenType::GREATER:        typeName = "GREATER"; break;
            case TokenType::GREATER_EQUAL:  typeName = "GREATER_EQUAL"; break;
            case TokenType::LOGICAL_AND:    typeName = "LOGICAL_AND"; break;
            case TokenType::LOGICAL_OR:     typeName = "LOGICAL_OR"; break;
            case TokenType::NOT:            typeName = "NOT"; break;
            case TokenType::LPAREN:         typeName = "LPAREN"; break;
            case TokenType::RPAREN:         typeName = "RPAREN"; break;
            case TokenType::LBRACE:         typeName = "LBRACE"; break;
            case TokenType::RBRACE:         typeName = "RBRACE"; break;
            case TokenType::LBRACKET:       typeName = "LBRACKET"; break;
            case TokenType::RBRACKET:       typeName = "RBRACKET"; break;
            case TokenType::SEMICOLON:      typeName = "SEMICOLON"; break;
            case TokenType::COMMA:          typeName = "COMMA"; break;
            case TokenType::DOT:            typeName = "DOT"; break;
            case TokenType::COMMENT:        typeName = "COMMENT"; break;
            case TokenType::WHITESPACE:     typeName = "WHITESPACE"; break;
            case TokenType::EOF_TOKEN:      typeName = "EOF"; break;
            case TokenType::ERROR:          typeName = "ERROR"; break;
            default:                        typeName = "UNKNOWN"; break;
        }
        return "(" + typeName + ", '" + value + "') [kolumna: " + std::to_string(column) + "]";
    }
};