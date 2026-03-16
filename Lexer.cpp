#include "Lexer.hpp"
using namespace std;

Lexer::Lexer(string source) {
    expression = source;
    pos = 0;
    column = 1;
    if (expression.length() > 0) curr = expression[pos];
    else curr = '\0';
}

void Lexer::advance() {
    pos++;
    column++;
    if (pos < expression.length()) {
        curr = expression[pos];
    } else curr = '\0';
}

void Lexer::skipWhiteSpace() {
    while (curr != '\0' && isspace(curr)) advance();
}

Token Lexer::getNumber() {
    string res = "";
    int startColumn = column;
    while (curr != '\0' && isdigit(curr)) {
        res += curr;
        advance();
    }
    return Token(TokenType::INT, res, startColumn);
}

Token Lexer::getId() {
    string res = "";
    int startColumn = column;
    while (curr != '\0' && isalpha(curr)) {
        res += curr;
        advance();
    }
    return Token(TokenType::ID, res, startColumn);
}

Token Lexer::getNextToken() {
    if (curr == '\0') {
        return Token(TokenType::EOF_TOKEN, "", column);
    } else if (isspace(curr)) {
        skipWhiteSpace();
        return getNextToken();
    } else if (isalpha(curr)) {
        return getId();
    } else if (isdigit(curr)) {
        return getNumber();
    } 
    
    int startColumn = column;
    
    if (curr == '+') {
        advance();
        return Token(TokenType::PLUS, "+", startColumn);
    } else if (curr == '-') {
        advance();
        return Token(TokenType::MINUS, "-", startColumn);
    } else if (curr == '*') {
        advance();
        return Token(TokenType::MULTIPLY, "*", startColumn);
    } else if (curr == '/') {
        advance();
        return Token(TokenType::DIVIDE, "/", startColumn);
    } else if (curr == '(') {
        advance();
        return Token(TokenType::LPAREN, "(", startColumn);
    } else if (curr == ')') {
        advance();
        return Token(TokenType::RPAREN, ")", startColumn);
    }
    
    string errorVal(1, curr);
    advance();
    return Token(TokenType::ERROR, errorVal, startColumn);
}