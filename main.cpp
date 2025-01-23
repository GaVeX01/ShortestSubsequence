#include <iostream>
#include <windows.h> 	
#include <chrono>
using namespace std;
using namespace std::chrono;

// bubble sort O(n^2)	
void sortDescending(int arr[], int n) { 
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Funkcja znajdująca najkrótszy podciąg o sumie większej niż k
void findShortestSubsequence(int arr[], int n, int k) { // cała funkcja ma złożoność O(n^2) przez sortowanie, gdyby zastosować quicksort O(n log n)
    // Wywołanie funkcji sortującej tablicę w porządku malejącym
    sortDescending(arr, n); // Funkcja sortująca tablicę arr o długości n w porządku malejącym

    // Inicjalizacja zmiennych pomocniczych
    int sum = 0; // Zmienna do przechowywania sumy elementów w podciągu
    int i = 0;   // Indeks, który będzie wskazywał liczbę elementów w najkrótszym podciągu

    // Szukamy najkrótszego podciągu o sumie większej niż k
    // Pętla przetwarza tablicę i sumuje elementy, dopóki suma nie przekroczy k
    while (i < n && sum <= k) {
        sum += arr[i]; // Dodajemy element z tablicy do sumy
        i++; // Przechodzimy do kolejnego elementu tablicy
    }

    // Sprawdzamy, czy znaleziono podciąg
    if (sum > k) {
        // Jeśli suma jest większa niż k, wypisujemy najkrótszy podciąg
        cout << "Najkrotszy podciag: ";
        for (int j = 0; j < i; j++) {  // Wypisujemy elementy podciągu
            cout << arr[j] << " "; // Wypisujemy element na pozycji j
        }
        cout << endl; // Koniec wypisywania
    } else {
        // Jeśli suma nigdy nie przekroczyła k
        cout << "Brak odpowiedniego podciagu!"<< endl;
    }
}

void findShortestSubsequenceSlidingWindow(int arr[], int n, int k) { // cała funkcja ma złożoność O(n) - każdy element jest przetwarzany maksymalnie raz
    // Inicjalizacja zmiennych pomocniczych
    int start = 0, sum = 0, minLength = INT_MAX, minStart = 0;
    // 'start' wskazuje początek okna, 'sum' to suma elementów w oknie
    // 'minLength' to długość najkrótszego podciągu, który spełnia warunek, domyślnie maksymalna wartość typu int
    // 'minStart' to indeks początkowy tego podciągu

    // Przesuwanie okna po tablicy
    for (int end = 0; end < n; end++) {
        sum += arr[end]; // Dodajemy element z pozycji 'end' do sumy okna

        // Zmniejszamy okno, gdy suma przekroczy wartość k
        while (sum > k) {
            // Sprawdzamy, czy obecne okno jest najkrótszym, które spełnia warunek
            if (end - start + 1 < minLength) {
                minLength = end - start + 1; // Aktualizujemy długość najkrótszego podciągu
                minStart = start; // Zapamiętujemy początek tego podciągu
            }

            // Usuwamy element od początku okna (przesuwamy wskaźnik 'start' w prawo)
            sum -= arr[start]; // Odejmujemy element, który zostaje usunięty z okna
            start++; // Przesuwamy początek okna w prawo
        }
    }

    // Sprawdzamy, czy znaleziono jakikolwiek podciąg
    if (minLength == INT_MAX) {
        // Jeśli długość pozostała maksymalna, to znaczy, że nie znaleziono podciągu
        cout << "Brak odpowiedniego podciagu!" << endl;
    } else {
        // Wypisujemy najkrótszy podciąg
        cout << "Najkrotszy podciag: ";
        for (int i = minStart; i < minStart + minLength; i++) {
            cout << arr[i] << " "; // Wypisujemy elementy najkrótszego podciągu
        }
        cout << endl; // Koniec wypisywania
    }
}


void findShortestSubsequenceDP(int arr[], int n, int k) { // w najgorszym przypadku O(n^2)
    // Tablica do przechowywania minimalnej długości podciągu dla danego indeksu
    int dp[n];  
    int minLength = INT_MAX; // Przechowuje globalną minimalną długość podciągu spełniającego warunek
    int minStart = -1, minEnd = -1; // Indeksy początku i końca znalezionego podciągu

    // Przechodzimy przez wszystkie indeksy i obliczamy najkrótszy podciąg
    for (int i = 0; i < n; i++) {
        int sum = 0; // Resetujemy sumę dla każdego indeksu
        dp[i] = INT_MAX; // Początkowo zakładamy, że nie ma podciągu

        for (int j = i; j < n; j++) {
            sum += arr[j]; // Dodajemy kolejne liczby do sumy

            if (sum > k) { // Jeśli suma przekroczyła k
                dp[i] = j - i + 1; // Długość podciągu to różnica indeksów + 1
                
                // Sprawdzamy, czy znaleziony podciąg jest krótszy niż poprzednie
                if (dp[i] < minLength) {
                    minLength = dp[i];
                    minStart = i;
                    minEnd = j;
                }
                break; // Przerywamy, bo znaleźliśmy minimalny podciąg dla tego i
            }
        }
    }

    // Wypisywanie wyniku
    if (minLength == INT_MAX) {
        cout << "Nie znaleziono podciagu, ktorego suma jest większa niz " << k << endl;
    } else {
        cout << "Najkrotszy podciag: ";
        for (int i = minStart; i <= minEnd; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Tworzenie tablicy liczb od 1 do SIZE
    const int SIZE = 10000; // n
    int numbers[SIZE];
    for (int i = 0; i < SIZE; i++) {
        numbers[i] = i + 1;
    }

    int k = 3000;  // liczba do przeważenia podciągiem

    // Pomiar czasu dla wersji 1
    cout << "wersja 1 (sortowanie i sumowanie):" << endl;
    auto start1 = high_resolution_clock::now();
    findShortestSubsequence(numbers, SIZE, k);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    cout << "Czas wykonania: " << duration1.count() << " mikroS\n" << endl; //1 sekunda = 1 000 000 mikrosekund

    // Pomiar czasu dla wersji 2
    cout << "wersja 2 (okno przesuwne):" << endl;
    auto start2 = high_resolution_clock::now();
    findShortestSubsequenceSlidingWindow(numbers, SIZE, k);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout << "Czas wykonania: " << duration2.count() << " mikroS\n" << endl;

    // Pomiar czasu dla wersji 3
    cout << "wersja 3 (brute force):" << endl;
    auto start3 = high_resolution_clock::now();
    findShortestSubsequenceDP(numbers, SIZE, k);
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3);
    cout << "Czas wykonania: " << duration3.count() << " mikroS\n" << endl;

    return 0;
}
