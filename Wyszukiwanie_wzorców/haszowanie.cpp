#include <iostream>
#include "string"
using namespace std;
#define size 13

struct node {
    node* next;
    string val;
};

int Hash(string Word) //hashuje mi s³owo za pomoc¹ jakiegoœ wzoru tu jest modulo 13 TO NAJWAZNIEJSZE reszta dzia³anie na listach
{
    int sum = 0;
    for (int i = 0; i < Word.length(); i++)
    {
        sum = sum + Word[i]; // to wypluje asci i doda 
    }
    return sum % (size); //zwracamy sume asci przez mod13
}

void add(node*& H, string x) //dodanie do listy zwykle
{
    node* p = new node;
    p->val = x;
    p->next = H;
    H = p;
}

void Del(node*& H)
{
    if (H != NULL)
    {
        node* p = H;
        H = p->next;
        delete p;
    }
}

void Del2(node*& H, string word)
{
    if (H != NULL) 
    {
        if (H->val == word)
        {
            Del(H);
        }
        else
        {
            node* p = H;
            while (p->next && p->next->val != word)
            {
                p = p->next;
            }
            if (p->next != NULL)
            {
                node* temp = p->next;
                p->next = p->next->next;
                delete temp;
            }
        }
    }
}

void PrintHashTable(node** tab) //taki show listowy
{
    for (int i = 0; i < size; i++)
    {
        cout << "Indeks " << i << ": ";
        node* current = tab[i];
        while (current != NULL)
        {
            cout << current->val << " ";
            current = current->next;
        }
        cout << endl;
    }
}

bool SearchInDB(node** tab, string word) //search listowy
{
    int hashValue = Hash(word); //hashujemy jakies slowo
    node* current = tab[hashValue]; //to co mi wyplulo to jest teraz w tej tablicy pod indeksem co mi wyplulo

    while (current != NULL)  //jesli nie jest pusta lista
    {
        if (current->val == word) //jesli to co tam jest jest szukane to swietnie
        {
            cout << "znaleziono";
            return true;
        }
        current = current->next; //jak nie to lecimy dalej po liscie
    }
    cout << "nie znaleziono";
    return false;
}

void AddToDB(node** tab, string word) //¿eby ³adniej bylo a  nie pisaæ takei brzydkie
{
    add(tab[Hash(word)], word);
}

void DelFromDB(node** tab, string word)
{
    Del2(tab[Hash(word)], word);
}



int main()
{


    node** tab = new node * [size]; //tablica wskaŸników na liste

    for (int i = 0; i < size; i++)
    {
        tab[i] = NULL;
    }

    string word = "ABs";
    AddToDB(tab, word);

    AddToDB(tab, word);

    string word2 = "adasvfv";
    AddToDB(tab, word2);


    //DelFromDB(tab, "ABs");
    //DelFromDB(tab, "ABs");

    PrintHashTable(tab);

    SearchInDB(tab, "ABss");
    return 0;
}

//dodajaca usuwajaca wyszkujaca wypisujaca```