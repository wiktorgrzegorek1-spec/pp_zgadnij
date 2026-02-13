************************************************************
             ZGADNIJ LICZBU - GRA KONSOLOWA C++
************************************************************

1. OPIS PROJEKTU
----------------
Prosta, tekstowa gra w ktorej gracz ma za zadanie odgadnac 
wylosowana przez komputer liczbe. Program oferuje rozne 
poziomy trudnosci, system zakladow oraz lokalny ranking.

2. FUNKCJE GRY
--------------
* Trzy poziomy trudnosci:
  - Latwy (1-50)
  - Sredni (1-100)
  - Trudny (1-250)
* System zakladow: Gracz moze ustalic limit prob. Przekroczenie
  limitu oznacza przegrana.
* Ranking TOP 5: Wyniki sa automatycznie sortowane i zapisywane
  w pliku "scores.txt".
* Multisystemowosc: Funkcja czyszczenia ekranu dziala na 
  Windowsie oraz Linuxie.

3. INSTRUKCJA URUCHOMIENIA
--------------------------
Wymagania: Kompilator C++ (np. MinGW, GCC, Clang).

Kompilacja:
  g++ -o gra_liczby main.cpp

Uruchomienie:
  Windows: gra_liczby.exe
  Linux:   ./gra_liczby

4. JAK GRAC?
------------
1. Wybierz '1' w menu glownym, aby rozpoczac.
2. Wybierz poziom trudnosci (1, 2 lub 3).
3. (Opcjonalnie) Zadeklaruj liczbe prob w zakladzie.
4. Wpisuj liczby, korzystajac z podpowiedzi "Za malo/Za duzo".
5. Po wygranej podaj imie - Twoj wynik trafi do rankingu,
   jesli zmiesci sie w piatce najlepszych.

5. STRUKTURA PLIKOW
-------------------
* main.cpp   - Kod zrodlowy programu.
* scores.txt - Plik bazy danych (tworzony automatycznie).
* README.txt - Niniejsza instrukcja.

------------------------------------------------------------
Autor: [Twoje Imie / Wikto]
Data: 2026
************************************************************
