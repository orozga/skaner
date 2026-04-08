# 🔍 Skaner i Syntax Highlighter

Skaner napisany w języku C++, służący do analizy składniowej uproszczonego języka programowania. Program przetwarza kod źródłowy na ciąg tokenów, a następnie generuje w pełni sformatowany i pokolorowany plik wynikowy w formacie HTML, zachowując oryginalny układ tekstu.

---

## Realizacja wymagań projektowych

* **Przygotowanie własnego spisu tokenów:** Zdefiniowano tabelę tokenów (wyliczenie `TokenType`), obejmującą słowa kluczowe, literały, operatory logiczne/arytmetyczne oraz interpunkcję.

* **Opracowanie diagramu przejść (Automat Skończony):** Logika przejść i rozpoznawania tokenów została zaimplementowana w klasie `Lexer`. Metody takie jak `getComment()`, `getStringLiteral()` czy `getNumber()` realizują poszczególne ścieżki i stany automatu (np. przejścia dla operatorów wieloznakowych `==`, `++`, `<<` czy komentarzy blokowych `/* ... */`).

* **Skaner rozpoznający tokeny:** Główna pętla programu poprawnie dzieli strumień wejściowy na atomy leksykalne i identyfikuje ich pozycję (wiersz, kolumna). Nieznane znaki są bezpiecznie wychwytywane jako tokeny `ERROR` bez przerywania pracy programu.

* **Kolorowanie składni (HTML):** Moduł `HtmlRenderer` przetwarza wygenerowane tokeny na znaczniki `<span>` z odpowiednimi klasami CSS, tworząc plik wynikowy.

* **Zachowanie układu tekstu:** Zaimplementowano dedykowane tokeny dla białych znaków (`WHITESPACE`) oraz znaków nowej linii (`NEWLINE`). Dzięki temu, w połączeniu ze znacznikami `<pre><code>`, plik wyjściowy HTML odwzorowuje oryginalne wcięcia z pliku wejściowego.

---

## Tabela Tokenów (Wybrany podzbiór)

Skaner rozpoznaje ponad 40 różnych tokenów, które można podzielić na następujące kategorie:

| Kategoria | Przykłady zidentyfikowanych tokenów |
| :--- | :--- |
| **Słowa kluczowe** | `int`, `return`, `if`, `else`, `while`, `for`, `bool`, `true`, `false` |
| **Literały** | `INT_LITERAL` (np. `42`), `STRING_LITERAL` (np. `"Hello"`), `CHAR_LITERAL` (np. `'c'`) |
| **Identyfikatory** | Zmienne i nazwy funkcji (np. `main`, `counter`, `std`) |
| **Operatory matematyczne** | `+`, `-`, `*`, `/`, `%`, `++`, `--` |
| **Operatory relacyjne i logiczne**| `==`, `!=`, `<`, `>`, `<=`, `>=`, `&&`, `||`, `!` |
| **Interpunkcja i struktura** | `(`, `)`, `{`, `}`, `[`, `]`, `;`, `,`, `.`, `::` |
| **Formatowanie i Inne** | `COMMENT` (`//...` oraz `/*...*/`), `WHITESPACE`, `NEWLINE`, `ERROR` |

---

## Architektura Projektu

Projekt został podzielony na komponenty:

* `Token.hpp` — Struktura danych reprezentująca pojedynczy leksem. Przechowuje typ (`enum class TokenType`), dopasowaną wartość tekstową oraz pozycję w kodzie źródłowym (wiersz i kolumnę).
* `Lexer.hpp` / `Lexer.cpp` — Główny silnik skanera. Analizuje strumień wejściowy znak po znaku, grupując je w tokeny na podstawie zdefiniowanych reguł automatu stanów.
* `HtmlRenderer.hpp` / `HtmlRenderer.cpp` — Odpowiada za warstwę prezentacji. Mapuje typy tokenów na odpowiednie klasy CSS i przeprowadza tzw. *HTML Escaping* (np. zamienia `<` na `&lt;`), chroniąc dokument wynikowy przed błędami renderowania.
* `main.cpp` — Punkt wejściowy aplikacji. Odpowiada za I/O (wczytanie pliku wejściowego, zapis do `index.html`) oraz orkiestrację przepływu danych między Lexerem a Rendererem. Na koniec automatycznie otwiera wynik w przeglądarce.

---

## Kompilacja i Uruchomienie

Projekt wykorzystuje system budowania **CMake**.

### Budowanie
W głównym katalogu projektu uruchom w terminalu następujące polecenia:
```bash
mkdir build
cd build
cmake ..
make