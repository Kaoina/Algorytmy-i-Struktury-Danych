#include<iostream>
#include<fstream>
using namespace std;

int** create_matrix(int &size) {
    fstream czytaj;
    czytaj.open("graf.txt");
    czytaj >> size;

    //stworzenie tablicy dwuwymiarowej (macierzy)
    int** M = new int* [size]; //tablica wska¿ników do wska¿ników
    for (int i = 0; i < size; i++)
        M[i] = new int[size];

    //uzupe³nienie tej tablicy wartoœciami z pliku
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            czytaj >> M[i][j];

    return M;
}

struct node {
    int to; //wierzcho³ek
    int dist; //to tez counter w queue
    node* next;
};
struct node_edge {
    int to;
    int dist;
    int from;
    node_edge* next;
};

void add_to_list(int to, int dst, node*& H) {
    node* p = new node;
    p->to = to;
    p->dist = dst;
    p->next = H;
    H = p;
}
void add_to_edge_list(int to, int from, int dst, node_edge*& H) {
    node_edge* p = new node_edge;
    p->to = to;
    p->from = from;
    p->dist = dst;
    p->next = H;
    H = p;
}

node** create_neighbourhood_list (int** M, int size) {
    //tworzenie pustej listy która bedzie wskazywaæ na kolejne listy
    node** LN = new node* [size]; //tablica wska¿ników do wska¿ników 
    for (int i = 0; i < size; i++)
        LN[i] = NULL; 

    //uzupe³nianie pierwszego wymiaru listy 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (M[i][j] != 0) {
                add_to_list(j+1, M[i][j], LN[i]);
            }
        }
    }

    return LN;
}
node_edge* create_edge_list(int** M, int size) {

    node_edge* LE = new node_edge;
    LE = NULL;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (M[i][j] != 0) {
                add_to_edge_list(i + 1, j + 1, M[i][j], LE);
            }
        }
    }

    return LE;
}
int* create_color_table(int size) {
    int* color_table = new int[size];
    for (int i = 0; i < size; i++) {
        color_table[i] = 0; //kolor domyœlny bia³y 
    }
    return color_table;
}

void show_matrix(int** M, int size) {
    for (int i = 0; i < size; i++) {
        cout << endl;
        for (int j = 0; j < size; j++) {
            cout << M[i][j] << " ";
        }
    }
    cout << "\n\n";
}
void show_list(node** H, int size) {

    for (int i = 0; i < size; i++) {
        cout << i+1 <<"H->";
        node* p = H[i];
        while (p != nullptr)
        {
            cout << " to" << p->to << ";dist" << p->dist << "  ->";
            p = p->next;

        }
        cout << "NULL" <<endl;
    }
    cout << "\n";
}
void show_edge_list(node_edge* H) {
    node_edge* p = H;

    while (p != NULL) {
        cout << "|" << p->to << "-" << p->from << "-" << p->dist << "|" << " -> ";
        p = p->next;
    }
    cout << "NULL\n\n";
}
void show_color_table(int* color_table, int size) {
    cout << "tablica kolorow: ";
    for (int i = 0; i < size; i++) {
        cout << color_table[i] << " ";
    }
    cout << "\n\n";
}

void del_matrix(int**& M, int r) {
    //usuniêcie drugiego wymiaru
    for (int i = 0; i < r; i++) {
        delete M[i];
    }
    //usuniecie pierwszego wymairu
    delete[] M;
    M = NULL;
}
void del_list(node**& LN, int size) {
    for (int i = 0; i < size; i++) {
        delete LN[i];
    }
    delete LN;
    LN = NULL;
}
void del_edge_list(node_edge*& H) {
    while (H != NULL) {
        node_edge* p = H;
        H = H->next;
        delete p;
    }
    H = NULL;
}

//przegl¹dnaie wszerz
void add_to_queue(node*& H, int to, int dist)
{
    node* p = H;

    if (p != NULL)
    {
        while (p->next != NULL) //idziemy na koniec
        {
            p = p->next;
        }
        p->next = new node; 
        p = p->next;
    }
    else //pusta lista
    {
       p = new node;
        H = p;
    }

    p->to = to;
    p->dist = dist;
    p->next = NULL;
}
void del_first_queue(node*& H) {
    if (H == NULL) {
        return;
    }
    node* p = H;
    H = H->next;
    delete p;
}
void breadth_first_search(node** LN, int*& color , int size) {
    
    node* Q = NULL; //pusta lista-kolejka jednokierunkowa

    int i = 0; //wybieramy od którego wierzcho³ka zaczynamy ale po indeksie czyli 0-6
     
            add_to_queue(Q, i + 1, 0);

            while (Q != NULL) { 
               // wypisanie pierwszego z kolejki i usuniêcie
                int current = Q->to;
                int counter = Q->dist;
                color[current - 1] = 2; // kolor czarny

                cout << "Odwiedzono: " << current << " counter: " << counter << endl;
                del_first_queue(Q); 
               // show_color_table(color, size);
                
                // dodawanie nieodwiedzonych s¹siadów
                node* p = LN[current - 1]; //sprawdzamy s¹siadów w odpowiedniej liscie
                while (p != NULL) { 
                    int neighbor = p->to; //przechowuje kolejne wierzcho³ki (sasaidów)
                  //cout << endl <<p->to<<endl; //do patrzenia na s¹siadów pokolei

                    if (color[neighbor - 1] == 0) { 
                        color[neighbor - 1] = 1; //kolor szary
                        add_to_queue(Q, neighbor, counter + 1); 
                    }
                    else {
                        p = p->next;
                    }
                }
            }
        
    cout << "\n";
}

//prim
void prim(node** LN, int size, int*& color_table) {
    int w = 1; //wybór wierzcho³ka
    color_table[w] = 1;

    node_edge* prim_list = NULL;
    int visited = 0; //zmienna do zapisania sk¹d jest
    node* min = NULL; //wkaznik na najmniejsza wartosc 
    node* p = NULL; //pomocniczy do chodzenia
    
    for (int i = 0; i < size - 1; i++){ //przedzodzimy tyle razy do ilu puntków musimy dojsc
        node* e = new node;
        int max = 0;

        for (int k = 0; k< size; k++) {
            e = LN[k];
            while (e != NULL) {
                if (e->dist > max) {
                    max = e->dist;
                }
                e = e->next;
            }
        }

        for (int j = 0; j < size; j++){ //chodzenie po tablicy szukajac pierwszego szarego
            if (color_table[j] == 1) { //wierzcho³ek czarny 

                p = LN[j];
                while (p != NULL) {

                    if (p->dist < max && color_table[p->to - 1] == 0) { //p->to to to wartoœæ s¹siada - musi byc bia³y 
                        visited = j;
                        max = p->dist;
                        min = p;   
                    }
                    p = p->next;
                }
            }
        }
        color_table[min->to - 1] = 1; //zmieniam kolor na czarny
        add_to_edge_list(min->to, visited+1 ,min->dist,prim_list);
    }
    show_edge_list(prim_list);
    return;
}

int main() {
    //macierz s¹siedztwa
    int rozmiar = 0;
    int** M = create_matrix(rozmiar);
    show_matrix(M, rozmiar);

    //lista s¹siedztwa
    node* H = NULL; 
    node** LN = create_neighbourhood_list (M, rozmiar);
    show_list(LN, rozmiar);

    //lista krawêdzi
    node_edge* LE = create_edge_list(M, rozmiar);
    show_edge_list(LE);

    //tablica kolorów
    int* color_table_bfs = create_color_table(rozmiar);
    show_color_table(color_table_bfs, rozmiar);

    //przegladanie wszerz
    breadth_first_search(LN, color_table_bfs, rozmiar);
    show_color_table(color_table_bfs, rozmiar);

    //algorytm Prima
   // sort(LN, rozmiar);
    int* color_table_prima = create_color_table(rozmiar);
    prim(LN, rozmiar, color_table_prima);

    //usuwanie tablic dynamicznych
    del_matrix(M, rozmiar);
    del_list(LN, rozmiar);
    del_edge_list(LE);
    delete[] color_table_bfs;
    delete[] color_table_prima;

    return 0;
}


