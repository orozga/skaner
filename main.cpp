#include <iostream>
#include "Lexer.hpp"

using namespace std;

Token skaner(Lexer& lexer) {
    Token token = lexer.getNextToken();
    
    if (token.type == TokenType::ERROR) {
        cerr << "-> BLAD SKANERA: Nierozpoznany znak '" << token.value 
             << "' w kolumnie " << token.column << "!" << endl;
    } else if (token.type != TokenType::EOF_TOKEN) {
        cout << "-> Wczytano: " << token.toString() << endl;
    }
    
    return token;
}

int main() {
    string expression = "2+3*(76+8/3)+ 3*(9-3)";
    cout << "Skanowanie wyrazenia: " << expression << "\n" << endl;
    
    Lexer lexer(expression);
    Token currentToken;
    
    do {
        currentToken = skaner(lexer);
    } while (currentToken.type != TokenType::EOF_TOKEN);

    cout << "\nKoniec analizy leksykalnej." << endl;
    return 0;
}