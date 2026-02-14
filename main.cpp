#include <iostream> //input/output stream (pozwala komunikowac sie z uzytkownikiem)
#include <vector> //działa jak tablica, w trakcie działania programu może się dynamicznie powiększać lub pomniejszać
#include <string> //pozwala korzystać z typu string, który jest wygodniejszy do pracy z tekstem niż tradycyjne tablice znaków
#include <fstream> //umożliwia pracę z plikami (czytanie i zapisywanie danych)
#include <algorithm> //zawiera funkcje do sortowania i innych operacji na kontenerach, takich jak wektory
#include <ctime> //umożliwia korzystanie z funkcji związanych z czasem, takich jak generowanie losowych liczb na podstawie aktualnego czasu
#include <cstdlib> //zawiera funkcje do generowania losowych liczb (rand) oraz do czyszczenia konsoli (system)

using namespace std;

// Struktura przechowujaca dane o wyniku gracza
struct Score {
   string name;
   int attempts;
   string difficulty;
};

// Funkcja sortujaca wyniki
bool compareScores(const Score& a, const Score& b) {
   return a.attempts < b.attempts;
}

// Funkcja do czyszczenia konsoli
void clearConsole() {
   #ifdef _WIN32
       system("cls");
   #else
       system("clear");
   #endif
}

// Funkcja rysujaca proste obramowanie (nasz "interfejs")
void drawHeader(string title) {
   cout << "========================================" << endl;
   cout << "      " << title << endl;
   cout << "========================================" << endl;
}

// Funkcja zapisu do pliku
void saveScore(Score s) {
   ofstream file("scores.txt", ios::app);
   if (file.is_open()) {
       file << s.name << " " << s.attempts << " " << s.difficulty << endl;
       file.close();
   }
}

// Funkcja wczytywania i wyswietlania TOP 5
void showTop5() {
   ifstream file("scores.txt");
   vector<Score> scores;
   string name, diff;
   int att;

   while (file >> name >> att >> diff) {
       scores.push_back({name, att, diff});
   }
   file.close();

   clearConsole();
   drawHeader("RANKING TOP 5");

   if (scores.empty()) {
       cout << "Brak zapisanych wynikow!" << endl;
   } else {
       sort(scores.begin(), scores.end(), compareScores);
      
       cout << "Poz.\tGracz\tProby\tPoziom" << endl;
       int limit = scores.size() < 5 ? scores.size() : 5;
       for (int i = 0; i < limit; i++) {
           cout << i + 1 << ".\t" << scores[i].name << "\t"
                << scores[i].attempts << "\t" << scores[i].difficulty << endl;
       }
   }
   cout << "\nNacisnij Enter, aby wrocic...";
   cin.ignore();
   cin.get();
}

// G³ówna funkcja gry
void playGame() {
   clearConsole();
   drawHeader("NOWA GRA");

   cout << "Wybierz poziom trudnosci:" << endl;
   cout << "1. Latwy (1-50)\n2. Sredni (1-100)\n3. Trudny (1-250)" << endl;
   int choice;
   cin >> choice;

   int maxRange = 100;
   string diffName = "Sredni";
   if (choice == 1) { maxRange = 50; diffName = "Latwy"; }
   else if (choice == 3) { maxRange = 250; diffName = "Trudny"; }

   // Tryb zak³adu
   int betAttempts = 0;
   cout << "Czy chcesz sie zalozyc o liczbe prob? (t/n): ";
   char betChoice;
   cin >> betChoice;
   if (betChoice == 't' || betChoice == 'T') {
       cout << "Podaj maksymalna liczbe prob: ";
       cin >> betAttempts;
   }

   // Losowanie liczby
   srand(time(0));
   int secretNumber = rand() % maxRange + 1;
   int guess = 0;
   int attempts = 0;
   bool won = false;

   string smallMsgs[] = {"Za malo!", "Sprobuj wyzej.", "Niestety, to za malo."};
   string bigMsgs[] = {"Za duzo!", "Celuj nizej.", "Przesadziles, za duza liczba."};

   while (true) {
       attempts++;
       clearConsole();
       drawHeader("ZGADUJ!");
       cout << "Poziom: " << diffName << " | Proba nr: " << attempts << endl;
      
       if (betAttempts > 0)
           cout << "Twoj zaklad: " << betAttempts << " prob." << endl;

       cout << "Podaj liczbe: ";
       cin >> guess;

       if (guess == secretNumber) {
           cout << "\nGRATULACJE! Trafiles w " << attempts << " probie!" << endl;
           won = true;
           break;
       } else if (guess < secretNumber) {
           cout << smallMsgs[rand() % 3] << endl;
       } else {
           cout << bigMsgs[rand() % 3] << endl;
       }

       if (betAttempts > 0 && attempts >= betAttempts) {
           cout << "\nPRZEGRANA! Wykorzystales limit prob w zakladzie." << endl;
           cout << "Prawidlowa liczba to: " << secretNumber << endl;
           break;
       }
      
       cout << "Nacisnij Enter, aby kontynuowac...";
       cin.ignore(); cin.get();
   }

   if (won) {
       cout << "Podaj swoje imie: ";
       string playerName;
       cin >> playerName;
       saveScore({playerName, attempts, diffName});
   } else {
       cout << "\nNacisnij Enter, aby wrocic...";
       cin.ignore(); cin.get();
   }
}

int main() {
   int menuChoice;
   do {
       clearConsole();
       drawHeader("MENU GLOWNE - ZGADNIJ LICZBE");
       cout << "1. Rozpocznij nowa gre" << endl;
       cout << "2. Ranking TOP 5" << endl;
       cout << "3. Wyjdz" << endl;
       cout << "\nWybor: ";
       cin >> menuChoice;

       switch (menuChoice) {
           case 1: playGame(); break;
           case 2: showTop5(); break;
       }
   } while (menuChoice != 3);
2;
   return 0;
}

