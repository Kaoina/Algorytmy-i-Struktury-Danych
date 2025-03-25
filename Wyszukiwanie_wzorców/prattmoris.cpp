#include <iostream>
#include <string>
using namespace std;

int main() {

    string ciag;
    string kod;
    cout << "Podaj ciag znakow: ";
    cin >> ciag;
    cout << endl;
    cout << "Podaj kod: ";
    cin >> kod;
    cout << endl;
    int LenKod = kod.length();
    //cout << LenKod << endl;
    int* tab = new int[LenKod];
    
    //tworzenie tabeli od patternu 
    for (int i = 0; i < LenKod; i++) {
        tab[i] = 0;
        for (int j = i; j > 0; j--) {
            string str1 = kod.substr(0, j); //substr wycina stringa //to wycina prefiks
            string str2 = kod.substr(i - j + 1, j); //podaje jej 1- gdzie zaczynam wycinaæ, 2- d³ugosc stringa ktory wycinam //to wycina sufix
            cout << str1 << " >> " << str2 << endl;
            if (str1 == str2) { //jesli sa rowne to znalezlismy cos 
                tab[i] = j; //to wpisujemy w meijsce wielkosc obecn¹ wycinka
                break;
            }
        }
    }

    //tablica pomocnicza z jednym wartownikem przed
    int* Kodtab = new int[LenKod + 1];
    Kodtab[0] = -1; //wartownik 
    for (int i = 1; i < LenKod + 1; i++) {
        Kodtab[i] = tab[i - 1];
    }

    //wypisanie tablicy któa stworyzlismy
    for (int i = 0; i < LenKod + 1; i++) {
        cout << Kodtab[i] << ", ";
    }

    //
    int LenCiag = ciag.length();
    int k = 0; //indeks kodu
    int c = 0; //indeks ciagu 
    while (c <= LenCiag + 1) { //idziemy az nie dojdziemy do konca ciagu
        if (k + 1 == LenKod) {
            break; //jak dojsdziemy do konca to znalelzismy slowo
        }
        if (ciag[c] == kod[k]) { //jeœli siê zgadza to obie zwieszkamy, idziemy w dobra storne 
            c++;
            k++;
        }
        //literki sie nie zgadzaja sa dwie opcje

        else if (k != 0) { //k nie jest na wartowniku, wiec przesuwamy je na miejsce ktore wskazuje indeks k w tym meijscu 
            k = Kodtab[k];
        }
        else if (k == 0) { //jenda opcja k jest na wwartowniku, wiec tylko przesuwamy c
            c++;
        }
    }

    if (k + 1 == LenKod) { //jesli wyszlismy zpêtli bo k siê skonczyli to znalezlismy kod
        cout << "Znaleziono kod" << endl;
    }
    else { //a jeœli nie to przeszlismy wysztsko i ni ebylo i lipa
        cout << "Nie znaleziono kodu" << endl;
    }
    delete[] tab;
    delete[] Kodtab;
}