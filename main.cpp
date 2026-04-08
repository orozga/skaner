#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Lexer.hpp"
#include "HtmlRenderer.hpp"

using namespace std;


Token skaner(Lexer& lexer) {
    Token token = lexer.getNextToken();
    
    if (token.type == TokenType::ERROR) {
        cerr << "[BLAD LEKSYKALNY] Nierozpoznany znak: '" << token.value
             << "' w kolumnie " << token.column << endl;
    } else if (token.type != TokenType::EOF_TOKEN) {
        cout << "-> " << token.toString() << endl;
    }
    return token;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uzycie: " << argv[0] << " <plik_zrodlowy>" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Nie mozna otworzyc pliku: " << filename << endl;
        return 1;
    }

    string expression;
    string line;
    while (getline(inFile, line)) {
        expression += line;
        if (!inFile.eof()) {
            expression += '\n';
        }
    }
    inFile.close();

    cout << "Skanowanie pliku: " << filename << "\n" << endl;
    cout << expression << "\n" << endl;

    Lexer lexer(expression);
    Token currentToken;
    
    do {
        currentToken = skaner(lexer);
    } while (currentToken.type != TokenType::EOF_TOKEN);
    
    const auto& tokens = lexer.getTokens();

    HtmlRenderer renderer;
    string htmlResult = renderer.generateColoredHTML(tokens);

    ofstream outFile("index.html");
    outFile << "<html><head><style>"
            << "body { background: #f8fafc; color: #263238; font-family: monospace; margin: 0; padding: 20px; } "
            << ".code-container { background: #ffffff; border: 1px solid #dfe3e8; padding: 18px; border-radius: 10px; box-shadow: 0 8px 24px rgba(0, 0, 0, 0.08); } "
            << ".token-int { color: #155fa0; } "
            << ".token-id { color: #2a6f3f; } "
            << ".token-keyword { color: #8f3d8f; font-weight: 700; } "
            << ".token-string { color: #b35c00; } "
            << ".token-char { color: #a65e25; } "
            << ".token-operator { color: #9c0592; } "
            << ".token-punct { color: #2d0178; } "
            << ".token-comment { color: #637381; font-style: italic; } "
            << "</style></head><body>" 
            << htmlResult 
            << "</body></html>";
    outFile.close();

    cout << "\nKoniec analizy leksykalnej." << endl;
    cout << "Gotowe! Otwórz index.html w przeglądarce." << endl;

    system("xdg-open index.html");

    return 0;
}