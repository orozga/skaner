#include "HtmlRenderer.hpp"

using namespace std;

static string escapeHtml(const string& text) {
    string escaped;
    for (char ch : text) {
        switch (ch) {
            case '&':  escaped += "&amp;"; break;
            case '<':  escaped += "&lt;"; break;
            case '>':  escaped += "&gt;"; break;
            case '"': escaped += "&quot;"; break;
            case '\'': escaped += "&#39;"; break;
            default:   escaped.push_back(ch); break;
        }
    }
    return escaped;
}

string HtmlRenderer::generateColoredHTML(const vector<Token>& tokens) {
    stringstream html;
    
    html << "<pre class='code-container'><code>";

    for (const auto& token : tokens) {
        string cssClass;
        
        switch (token.type) {
            case TokenType::INT_LITERAL:    cssClass = "token-int"; break;
            case TokenType::STRING_LITERAL: cssClass = "token-string"; break;
            case TokenType::CHAR_LITERAL:   cssClass = "token-char"; break;
            case TokenType::IDENTIFIER:     cssClass = "token-id"; break;
            case TokenType::KEYWORD:        cssClass = "token-keyword"; break;
            case TokenType::PLUS:
            case TokenType::MINUS:
            case TokenType::MULTIPLY:
            case TokenType::DIVIDE:
            case TokenType::MODULO:
            case TokenType::INCREMENT:
            case TokenType::DECREMENT:
            case TokenType::ASSIGN:
            case TokenType::EQUAL:
            case TokenType::NOT_EQUAL:
            case TokenType::LESS:
            case TokenType::LESS_EQUAL:
            case TokenType::GREATER:
            case TokenType::GREATER_EQUAL:
            case TokenType::LEFT_SHIFT:
            case TokenType::RIGHT_SHIFT:
            case TokenType::LOGICAL_AND:
            case TokenType::LOGICAL_OR:
            case TokenType::NOT:
                cssClass = "token-operator";
                break;
            case TokenType::LPAREN:
            case TokenType::RPAREN:
            case TokenType::LBRACE:
            case TokenType::RBRACE:
            case TokenType::LBRACKET:
            case TokenType::RBRACKET:
            case TokenType::SEMICOLON:
            case TokenType::COMMA:
            case TokenType::DOT:
            case TokenType::HASH:
            case TokenType::SCOPE_RESOLUTION:
                cssClass = "token-punct";
                break;
            case TokenType::COMMENT:
                cssClass = "token-comment";
                break;
            case TokenType::WHITESPACE:
            case TokenType::NEWLINE:
                cssClass = "token-whitespace";
                break;
            default:                        cssClass = ""; break;
        }

        const string escapedValue = escapeHtml(token.value);
        if (!cssClass.empty()) {
            html << "<span class=\"" << cssClass << "\">" << escapedValue << "</span>";
        } else {
            html << escapedValue;
        }
    }

    html << "</code></pre>";
    return html.str();
}