#include "Lexer.hpp"
#include <unordered_set>

using namespace std;

static bool isIdentifierStart(char ch) {
    return isalpha(static_cast<unsigned char>(ch)) || ch == '_';
}

static bool isIdentifierPart(char ch) {
    return isalnum(static_cast<unsigned char>(ch)) || ch == '_';
}

static const unordered_set<string> keywords = {
    "int", "return", "if", "else", "while", "for", "break",
    "continue", "void", "char", "bool", "true", "false"
};

Lexer::Lexer(string source) {
    expression = source;
    pos = 0;
    column = 1;
    if (expression.length() > 0) curr = expression[pos];
    else curr = '\0';
    tokens = vector<Token>();
}

void Lexer::advance() {
    pos++;
    column++;
    if (pos < expression.length()) {
        curr = expression[pos];
    } else {
        curr = '\0';
    }
}

Token Lexer::getNumber() {
    string res;
    int startColumn = column;
    while (curr != '\0' && isdigit(static_cast<unsigned char>(curr))) {
        res += curr;
        advance();
    }
    return Token(TokenType::INT_LITERAL, res, startColumn);
}

Token Lexer::getIdentifierOrKeyword() {
    string res;
    int startColumn = column;
    while (curr != '\0' && isIdentifierPart(curr)) {
        res += curr;
        advance();
    }
    if (keywords.count(res) > 0) {
        return Token(TokenType::KEYWORD, res, startColumn);
    }
    return Token(TokenType::IDENTIFIER, res, startColumn);
}

Token Lexer::getStringLiteral() {
    string res;
    int startColumn = column;
    res += curr;
    advance();

    while (curr != '\0') {
        res += curr;
        if (curr == '\\') {
            advance();
            if (curr != '\0') {
                res += curr;
            }
        } else if (curr == '"') {
            advance();
            return Token(TokenType::STRING_LITERAL, res, startColumn);
        }
        advance();
    }

    return Token(TokenType::ERROR, res, startColumn);
}

Token Lexer::getCharLiteral() {
    string res;
    int startColumn = column;
    res += curr;
    advance();

    if (curr == '\\') {
        res += curr;
        advance();
        if (curr != '\0') {
            res += curr;
            advance();
        }
    } else if (curr != '\0') {
        res += curr;
        advance();
    }

    if (curr == '\'') {
        res += curr;
        advance();
        return Token(TokenType::CHAR_LITERAL, res, startColumn);
    }

    return Token(TokenType::ERROR, res, startColumn);
}

Token Lexer::getComment() {
    string res;
    int startColumn = column;
    res += curr;
    advance();

    if (curr == '/') {
        res += curr;
        advance();
        while (curr != '\0' && curr != '\n') {
            res += curr;
            advance();
        }
        return Token(TokenType::COMMENT, res, startColumn);
    }

    if (curr == '*') {
        res += curr;
        advance();
        while (curr != '\0') {
            if (curr == '*') {
                res += curr;
                advance();
                if (curr == '/') {
                    res += curr;
                    advance();
                    break;
                }
            } else {
                res += curr;
                advance();
            }
        }
        return Token(TokenType::COMMENT, res, startColumn);
    }

    return Token(TokenType::DIVIDE, "/", startColumn);
}

Token Lexer::getWhitespace() {
    string res;
    int startColumn = column;
    while (curr != '\0' && isspace(static_cast<unsigned char>(curr))) {
        res += curr;
        advance();
    }
    return Token(TokenType::WHITESPACE, res, startColumn);
}

Token Lexer::getNextToken() {
    if (curr == '\0') {
        return Token(TokenType::EOF_TOKEN, "", column);
    }

    int startColumn = column;
    Token t;

    if (isspace(static_cast<unsigned char>(curr))) {
        t = getWhitespace();
    } else if (isIdentifierStart(curr)) {
        t = getIdentifierOrKeyword();
    } else if (isdigit(static_cast<unsigned char>(curr))) {
        t = getNumber();
    } else if (curr == '"') {
        t = getStringLiteral();
    } else if (curr == '\'') {
        t = getCharLiteral();
    } else if (curr == '/') {
        int lookaheadPos = pos + 1;
        if (lookaheadPos < expression.length() &&
            (expression[lookaheadPos] == '/' || expression[lookaheadPos] == '*')) {
            t = getComment();
        } else {
            advance();
            t = Token(TokenType::DIVIDE, "/", startColumn);
        }
    } else if (curr == '+') {
        advance();
        if (curr == '+') {
            advance();
            t = Token(TokenType::INCREMENT, "++", startColumn);
        } else {
            t = Token(TokenType::PLUS, "+", startColumn);
        }
    } else if (curr == '-') {
        advance();
        if (curr == '-') {
            advance();
            t = Token(TokenType::DECREMENT, "--", startColumn);
        } else {
            t = Token(TokenType::MINUS, "-", startColumn);
        }
    } else if (curr == '*') {
        advance();
        t = Token(TokenType::MULTIPLY, "*", startColumn);
    } else if (curr == '%') {
        advance();
        t = Token(TokenType::MODULO, "%", startColumn);
    } else if (curr == '=') {
        advance();
        if (curr == '=') {
            advance();
            t = Token(TokenType::EQUAL, "==", startColumn);
        } else {
            t = Token(TokenType::ASSIGN, "=", startColumn);
        }
    } else if (curr == '!') {
        advance();
        if (curr == '=') {
            advance();
            t = Token(TokenType::NOT_EQUAL, "!=", startColumn);
        } else {
            t = Token(TokenType::NOT, "!", startColumn);
        }
    } else if (curr == '<') {
        advance();
        if (curr == '=') {
            advance();
            t = Token(TokenType::LESS_EQUAL, "<=", startColumn);
        } else {
            t = Token(TokenType::LESS, "<", startColumn);
        }
    } else if (curr == '>') {
        advance();
        if (curr == '=') {
            advance();
            t = Token(TokenType::GREATER_EQUAL, ">=", startColumn);
        } else {
            t = Token(TokenType::GREATER, ">", startColumn);
        }
    } else if (curr == '&') {
        advance();
        if (curr == '&') {
            advance();
            t = Token(TokenType::LOGICAL_AND, "&&", startColumn);
        } else {
            t = Token(TokenType::ERROR, "&", startColumn);
        }
    } else if (curr == '|') {
        advance();
        if (curr == '|') {
            advance();
            t = Token(TokenType::LOGICAL_OR, "||", startColumn);
        } else {
            t = Token(TokenType::ERROR, "|", startColumn);
        }
    } else if (curr == '(') {
        advance();
        t = Token(TokenType::LPAREN, "(", startColumn);
    } else if (curr == ')') {
        advance();
        t = Token(TokenType::RPAREN, ")", startColumn);
    } else if (curr == '{') {
        advance();
        t = Token(TokenType::LBRACE, "{", startColumn);
    } else if (curr == '}') {
        advance();
        t = Token(TokenType::RBRACE, "}", startColumn);
    } else if (curr == '[') {
        advance();
        t = Token(TokenType::LBRACKET, "[", startColumn);
    } else if (curr == ']') {
        advance();
        t = Token(TokenType::RBRACKET, "]", startColumn);
    } else if (curr == ';') {
        advance();
        t = Token(TokenType::SEMICOLON, ";", startColumn);
    } else if (curr == ',') {
        advance();
        t = Token(TokenType::COMMA, ",", startColumn);
    } else if (curr == '.') {
        advance();
        t = Token(TokenType::DOT, ".", startColumn);
    } else {
        string errorVal(1, curr);
        advance();
        t = Token(TokenType::ERROR, errorVal, startColumn);
    }

    tokens.push_back(t);
    return t;
}

const vector<Token>& Lexer::getTokens() {
    return tokens;
}
