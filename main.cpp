#include <iostream> // Podstawowe wejście/wyjście
#include <vector> // Do przechowywania wyników w pamięci
#include <string> // Do obsługi tekstu (imiona, poziomy trudności)
#include <fstream> // Do zapisywania i odczytywania wyników z pliku
#include <algorithm> // Do sortowania wyników
#include <ctime> // Do generowania losowej liczby
#include <cstdlib> // Do system("cls") i system("clear")
#include <limits> // Potrzebne do naprawy błędu z wpisywaniem liter

using namespace std;

// Struktura przechowująca dane o wyniku
struct Score {
    string name;
    int attempts;
    string difficulty;
};

// Funkcja sortująca wyniki
bool compareScores(const Score& a, const Score& b) {
    return a.attempts < b.attempts;
}

// Funkcja czyszcząca ekran (działa na Windows i Linux/Mac)
void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Sprawdzenie czy plik z wynikami istnieje i nie jest pusty
bool hasScores() {
    ifstream file("scores.txt");
    string test;
    // Próbujemy wczytać pierwsze słowo, jeśli się nie uda -> plik pusty
    if (!(file >> test)) return false;
    return true;
}

// Bezpieczne wczytywanie liczby (zabezpieczenie przed literami)
int getSafeInt() {
    int val;
    while (!(cin >> val)) {
        // Jeśli użytkownik wpisał litery zamiast liczby:
        cout << "\033[A\r\033[K"; // Usuń linię z błędem (dla estetyki)
        cout << "Wpisz liczbę 1-3! Sprobuj ponownie: ";
        cin.clear(); // Wyczyść flagę błędu
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Usuń śmieci z bufora
    }
    return val;
}

void drawHeader(string title) {
    cout << "========================================" << endl;
    cout << "      " << title << endl;
    cout << "========================================" << endl;
}

void saveScore(Score s) {
    ofstream file("scores.txt", ios::app);
    if (file.is_open()) {
        file << s.name << " " << s.attempts << " " << s.difficulty << endl;
        file.close();
    }
}

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

    sort(scores.begin(), scores.end(), compareScores);
    
    cout << "Poz.\tGracz\tProby\tPoziom" << endl;
    int limit = (scores.size() < 5) ? scores.size() : 5;
    for (int i = 0; i < limit; i++) {
        cout << i + 1 << ".\t" << scores[i].name << "\t"
             << scores[i].attempts << "\t" << scores[i].difficulty << endl;
    }
    
    cout << "\nNacisnij Enter, aby wrocic...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Czeka na czysty Enter
    cin.get();
}

void playGame() {
    clearConsole();
    drawHeader("NOWA GRA");

    cout << "Wybierz poziom (1.Latwy, 2.Sredni, 3.Trudny): ";
    int choice = getSafeInt();

    int maxRange = 100;
    string diffName = "Sredni";
    if (choice == 1) { maxRange = 50; diffName = "Latwy"; }
    else if (choice == 3) { maxRange = 250; diffName = "Trudny"; }

    cout << "Czy chcesz limit prob? (t/n): ";
    char betChoice;
    cin >> betChoice;
    int betAttempts = 0;
    if (betChoice == 't' || betChoice == 'T') {
        cout << "Podaj limit: ";
        betAttempts = getSafeInt();
    }

    srand(time(0));
    int secretNumber = rand() % maxRange + 1;
    int guess = 0;
    int attempts = 0;
    bool won = false;

    // Zmienna przechowująca komunikat o wyniku (Za mało/Za dużo)
    string lastInfo = ""; 

    clearConsole();
    drawHeader("ZGADUJ LICZBE!");
    cout << "Zakres: 1 - " << maxRange << " | Poziom: " << diffName << endl;
    if (betAttempts > 0) cout << "Limit prob: " << betAttempts << endl;
    cout << "----------------------------------------" << endl;
    cout << "\n"; // Pusta linia startowa

    while (true) {
        attempts++;
        
        // --- SEKCJA ESTETYCZNA (Nadpisywanie linii) ---
        // Jeśli to nie jest pierwsza próba, usuwamy dwie poprzednie linie:
        // 1. Linię, w której użytkownik wpisał liczbę i wcisnął Enter
        // 2. Linię z pytaniem "Podaj liczbę"
        if (attempts > 1) {
            cout << "\033[A\r\033[K"; // Kursor w górę -> Początek linii -> Wyczyść linię
            cout << "\033[A\r\033[K"; // Powtórka dla drugiej linii
        }

        // Wyświetlamy aktualny stan + komunikat z POPRZEDNIEJ tury
        cout << "Proba " << attempts << ". " << lastInfo << " Podaj liczbe: ";
        
        guess = getSafeInt(); // Tutaj czekamy na wpisanie liczby i Enter

        // Sprawdzamy wynik
        if (guess == secretNumber) {
            cout << "\n>> GRATULACJE! Trafiles w " << attempts << " probie!" << endl;
            won = true;
            break;
        } else {
            // Zapisujemy podpowiedź do zmiennej, wyświetlimy ją dopiero
            // na początku następnej pętli (dzięki temu nie mignie i zniknie)
            if (guess < secretNumber) lastInfo = "[ZA MALO]";
            else lastInfo = "[ZA DUZO]";
        }

        // Sprawdzenie zakładu
        if (betAttempts > 0 && attempts >= betAttempts) {
            cout << "\nPRZEGRANA! Limit wykorzystany. Liczba to: " << secretNumber << endl;
            break;
        }
    }

    if (won) {
        cout << "Podaj imie do rankingu (bez spacji): ";
        string playerName;
        cin >> playerName;
        saveScore({playerName, attempts, diffName});
    }
    
    cout << "\nNacisnij Enter, aby wrocic do menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    // Magiczna linijka, która włącza obsługę kodów sterujących (kolorów/kursora) w Windows 10/11
    #ifdef _WIN32
        system(" "); 
    #endif

    int menuChoice;
    do {
        // Sprawdzamy dostępność rankingu przed narysowaniem menu
        bool showRanking = hasScores(); 

        clearConsole();
        drawHeader("MENU GLOWNE");
        cout << "1. Rozpocznij nowa gre" << endl;
        
        // Wyświetlamy opcję 2 tylko jeśli są wyniki
        if (showRanking) {
            cout << "2. Ranking TOP 5" << endl;
        }
        
        cout << "3. Wyjdz" << endl;
        cout << "\nWybor: ";
        
        // Używamy bezpiecznego wczytywania (nie zatnie się na literach)
        menuChoice = getSafeInt();

        if (menuChoice == 1) {
            playGame();
        } else if (menuChoice == 2 && showRanking) {
            showTop5();
        }
        // Jeśli użytkownik wpisze 2, a rankingu nie ma -> nic się nie stanie (pętla wróci)

    } while (menuChoice != 3);

    return 0;
}
