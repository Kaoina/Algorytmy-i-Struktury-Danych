#include <iostream>
#include "string"
using namespace std;

void Naive(string txt, string pat)
{
    int LenTXT = txt.length();
    int LenPat = pat.length();
    int i = 0, j;
    while (i <= LenTXT - LenPat)// zeby nie szlo do konca nawet jak brakuje liter
    {
        j = 0;
        while (j < LenPat && pat[j] == txt[i + j]) //zrobi sie tyle razy ile znak�w ma wzorzec, por�wnuje elementy string�w (kt�e traktuejmy ajko tablice)
        {
            j++;
            if (j == LenPat)
            {
                cout << "Wzorzecz znaleziony na indeksie: " << i << endl;
                return;
            }
        }  //nie pami�ta co robi� wcze�niej

        i++;
    }
    cout << "Nie znaleziono" << endl;
}

int main()
{
    string txt = "abABQWEabASBRTYQWERTYAB";
    string pattern = "AB";
    Naive(txt, pattern);

    return 0;
}