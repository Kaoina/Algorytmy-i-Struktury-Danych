#include <iostream>
#include <string>
using namespace std;
#define d 10

//szukamy paternu w stringu
void KarpRabin(string pattern, string text, int q) {
    int LenPat = pattern.length();
    int LenTxt = text.length();
    int i, j;  
    int p = 0;  // hasz dla wzorca
    int t = 0; // hasz dla tekstu
    int h = 1;

    //liczenie maksymalnej potegi do usuwania
    for (i = 0; i < LenPat - 1; i++)
        h = (h * d) % q; //co każde przejscie zwieksza mi jakby potege 

  //LICZNENIE WARTOSC HAShU DLA POTENGI i pierwszych znakow
    for (i = 0; i < LenPat; i++) {
        p = ((d * p) + pattern[i]) % q; 
        t = ((d * t) + text[i]) % q;
    }

    //porownywanie w tekscie
    for (i = 0; i <= LenTxt - LenPat; i++) {
        if (p == t) {
            for (j = 0; j < LenPat; j++) {
                if (text[i + j] != pattern[j]) //jesli sobie jednak nie jest rowne to lipa
                    break; //no bo wartosc moze byc ta sama z mod ale literki nie koneicznie, zastosowanie algorytmy karpia 
                //tylko zmniejsza szanse na wystapienie takeij sytuacji
            }
            if (j == LenPat)
                cout << "Znaleziono wzorzec na ideksie: " << i << endl;
        }
        //no to jest po wyrzuceniu z fukcji jak nei byly te same wzorce jednak
        if (i < LenTxt - LenPat) {
            t = (d * (t - text[i] * h) + text[i + LenPat]) % q; //przesuwam o jedno 

            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    string text = "ABCCDDAESFIDHGEURFHGOUGEUHEROIGHEUROERIGHEROIGHEROEURIGEFG";
    string pattern = "EUR";
    int q = 13;
    KarpRabin(pattern, text, q);
}