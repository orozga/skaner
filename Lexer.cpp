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
    row = 1;
    column = 1;
    if (expression.length() > 0) curr = expression[pos];
    else curr = '\0';
    tokens = vector<Token>();
}

void Lexer::advance() {
    pos++;
    if (curr == '\n') {
        row++;
        column = 1;
    } else {
        column++;
    }
    if (pos < expression.length()) {
        curr = expression[pos];
    } else {
        curr = '\0';
    }
}

Token Lexer::getNumber() {
    string res;
    int startRow = row;
    int startColumn = column;
    while (curr != '\0' && isdigit(static_cast<unsigned char>(curr))) {
        res += curr;
        advance();
    }
    return Token(TokenType::INT_LITERAL, res, startRow, startColumn);
}

Token Lexer::getIdentifierOrKeyword() {
    string res;    int startRow = row;    int startColumn = column;
    while (curr != '\0' && isIdentifierPart(curr)) {
        res += curr;
        advance();
    }
    if (keywords.count(res) > 0) {
        return Token(TokenType::KEYWORD, res, startRow, startColumn);
    }
    return Token(TokenType::IDENTIFIER, res, startRow, startColumn);
}

Token Lexer::getStringLiteral() {
    string res;
    int startRow = row;
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
            return Token(TokenType::STRING_LITERAL, res, startRow, startColumn);
        }
        advance();
    }

    return Token(TokenType::ERROR, res, startRow, startColumn);
}

Token Lexer::getCharLiteral() {
    string res;
    int startRow = row;
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
        return Token(TokenType::CHAR_LITERAL, res, startRow, startColumn);
    }

    return Token(TokenType::ERROR, res, startRow, startColumn);
}

Token Lexer::getComment() {
    string res;
    int startRow = row;
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
        return Token(TokenType::COMMENT, res, startRow, startColumn);
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
        return Token(TokenType::COMMENT, res, startRow, startColumn);
    }

    return Token(TokenType::DIVIDE, "/", startRow, startColumn);
}

Token Lexer::getWhitespace() {
    string res;
    int startRow = row;
    int startColumn = column;
    while (curr != '\0' && isspace(static_cast<unsigned char>(curr)) && curr != '\n') {
        res += curr;
        advance();
    }
    return Token(TokenType::WHITESPACE, res, startRow, startColumn);
}

Token Lexer::getNextToken() {
    if (curr == '\0') {
        return Token(TokenType::EOF_TOKEN, "", row, column);
    }

    int startRow = row;
    int startColumn = column;
    Token t;

    if (curr == '\n') {
        advance();
        t = Token(TokenType::NEWLINE, "\n", startRow, startColumn);
    } else if (isspace(static_cast<unsigned char>(curr))) {
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
            t = Token(TokenType::DIVIDE, "/", startRow, startColumn);
        }
    } else if (curr == '+') {
        advance();
        if (curr == '+') {
            advance();
            t = Token(TokenType::INCREMENT, "++", startRow, startColumn);
        } else {
            t = Token(TokenType::PLUS, "+", startRow, startColumn);
        }
    } else if (curr == '-') {
        advance();
        if (curr == '-') {
            advance();
            t = Token(TokenType::DECREMENT, "--", startRow, startColumn);
        } else {
            t = Token(TokenType::MINUS, "-", startRow, startColumn);
        }
    } else if (curr == '*') {
        advance();
        t = Token(TokenType::MULTIPLY, "*", startRow, startColumn);
    } else if (curr == '%') {
        advance();
        t = Token(TokenType::MODULO, "%", startRow, startColumn);
    } else if (curr == '=') {
        advance();
        if (curr == '=') {
            advance();
            t = Token(TokenType::EQUAL, "==", startRow, startColumn);
        } else {
            t = Token(TokenType::ASSIGN, "=", startRow, startColumn);
        }
    } else if (curr == '!') {
        advance();
        if (curr == '=') {
            advance();
            t = Token(TokenType::NOT_EQUAL, "!=", startRow, startColumn);
        } else {
            t = Token(TokenType::NOT, "!", startRow, startColumn);
        }
    } else if (curr == '<') {
        advance();
        if (curr == '<') {
            advance();
            t = Token(TokenType::LEFT_SHIFT, "<<", startRow, startColumn);
        } else if (curr == '=') {
            advance();
            t = Token(TokenType::LESS_EQUAL, "<=", startRow, startColumn);
        } else {
            t = Token(TokenType::LESS, "<", startRow, startColumn);
        }
    } else if (curr == '>') {
        advance();
        if (curr == '>') {
            advance();
            t = Token(TokenType::RIGHT_SHIFT, ">>", startRow, startColumn);
        } else if (curr == '=') {
            advance();
            t = Token(TokenType::GREATER_EQUAL, ">=", startRow, startColumn);
        } else {
            t = Token(TokenType::GREATER, ">", startRow, startColumn);
        }
    } else if (curr == '&') {
        advance();
        if (curr == '&') {
            advance();
            t = Token(TokenType::LOGICAL_AND, "&&", startRow, startColumn);
        } else {
            t = Token(TokenType::ERROR, "&", startRow, startColumn);
        }
    } else if (curr == '|') {
        advance();
        if (curr == '|') {
            advance();
            t = Token(TokenType::LOGICAL_OR, "||", startRow, startColumn);
        } else {
            t = Token(TokenType::ERROR, "|", startRow, startColumn);
        }
    } else if (curr == '(') {
        advance();
        t = Token(TokenType::LPAREN, "(", startRow, startColumn);
    } else if (curr == ')') {
        advance();
        t = Token(TokenType::RPAREN, ")", startRow, startColumn);
    } else if (curr == '{') {
        advance();
        t = Token(TokenType::LBRACE, "{", startRow, startColumn);
    } else if (curr == '}') {
        advance();
        t = Token(TokenType::RBRACE, "}", startRow, startColumn);
    } else if (curr == '[') {
        advance();
        t = Token(TokenType::LBRACKET, "[", startRow, startColumn);
    } else if (curr == ']') {
        advance();
        t = Token(TokenType::RBRACKET, "]", startRow, startColumn);
    } else if (curr == ';') {
        advance();
        t = Token(TokenType::SEMICOLON, ";", startRow, startColumn);
    } else if (curr == ',') {
        advance();
        t = Token(TokenType::COMMA, ",", startRow, startColumn);
    } else if (curr == '.') {
        advance();
        t = Token(TokenType::DOT, ".", startRow, startColumn);
    } else if (curr == '#') {
        advance();
        t = Token(TokenType::HASH, "#", startRow, startColumn);
    } else if (curr == ':') {
        advance();
        if (curr == ':') {
            advance();
            t = Token(TokenType::SCOPE_RESOLUTION, "::", startRow, startColumn);
        } else {
            t = Token(TokenType::ERROR, ":", startRow, startColumn);
        }
    } else {
        string errorVal(1, curr);
        advance();
        t = Token(TokenType::ERROR, errorVal, startRow, startColumn);
    }

    tokens.push_back(t);
    return t;
}

const vector<Token>& Lexer::getTokens() {
    return tokens;
}
