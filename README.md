# Skaner Wyrażeń Matematycznych 

## Funkcjonalności i Zakres Projektu
Program obsługuje pełny proces skanowania leksykalnego, w tym:
* **Rozpoznawanie tokenów wielowartościowych**:
    * Liczby całkowite (`INT`) - np. `2`, `76`, `300`.
    * Identyfikatory (`ID`) - np. nazwy zmiennych złożone z liter.
* **Rozpoznawanie tokenów jednowartościowych**:
    * Operatory arytmetyczne: `+`, `-`, `*`, `/`.
    * Nawiasy: `(`, `)`.
* **Automatyczne pomijanie białych znaków**: Skuteczne ignorowanie spacji i tabulacji między tokenami.
* **Lokalizacja błędów**: Każdy token przechowuje numer kolumny, w której się rozpoczyna, co ułatwia debugowanie kodu źródłowego.
* **Inteligentna obsługa błędów**: Program nie przerywa pracy po napotkaniu nieznanego znaku; zamiast tego generuje token błędu (`ERROR`) i kontynuuje analizę pozostałej części wyrażenia.

## Architektura Systemu
* **`Token.hpp`**: Definicja klasy `Token` oraz typu wyliczeniowego `TokenType`. Zawiera metodę `toString()`, która formatuje wyjście do postaci czytelnej dla użytkownika.
* **`Lexer.hpp / Lexer.cpp`**: Główna logika analizatora. Implementuje automat skończony rozpoznający poszczególne symbole.
* **`main.cpp`**: Funkcja sterująca, która w pętli wywołuje skaner aż do napotkania końca wyrażenia (`EOF`).

## Przykład Wyniku Działania
Dla wyrażenia wejściowego: `2 + 3 * (76 + 8 / 3)`
Program generuje wyjście w formacie:
`-> (INT(2), '2') [kolumna: 1]`
`-> (PLUS, '+') [kolumna: 3]`
`-> (INT(3), '3') [kolumna: 5]`
...

W przypadku błędnego znaku (np. `2 @ 3`):
`[BŁĄD LEKSYKALNY] Nierozpoznany znak: '@' w kolumnie 3`