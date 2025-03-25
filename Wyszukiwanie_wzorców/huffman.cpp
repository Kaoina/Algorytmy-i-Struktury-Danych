#include <iostream>
#include <string>
#include <map>
using namespace std;

struct tree {
    char val;         // wystarczy na int zmienic typ 
    tree* L = NULL;
    tree* R = NULL;
    tree* par = NULL;
};

struct node {
    int val;
    node* par = NULL;
    node* next;
    tree* tree;
};

void addToList(node*& H, int x, int i) {

    node* p = new node;
    p->val = x;
    p->next = H;
    //p->par = p;        // dodane
    tree* t = new tree;
    t->val = i;
    p->tree = t;
    if (H != NULL) {
        p->next->par = p;
    }
    H = p;

}

void show(node* H) {
    std::cout << "H->";
    node* p = H;
    while (p != NULL) {
        std::cout << p->val << "->";
        p = p->next;
    }
    std::cout << "NULL" << std::endl;
}

void show2(node* H) {
    std::cout << "H->";
    node* p = H;
    while (p != NULL) {
        std::cout << p->val << "->";
        p = p->par;
    }
    std::cout << "NULL" << std::endl;
}
void stringToArray(string s, int tablica[255]) {
    int tablicaASCII[255];
    for (int i = 0; i < 255; i++) {
        tablica[i] = 0;
    }
    for (int i = 0; i < s.length(); i++) {
        char x = s[i]; // daje do zmiennej literki pokolei pojedynczo
        //cout << int(x) << endl;
        tablica[(int)x]++; //to mi zwiekszy iloœæ danej litery w indeksie 
    }
}

void createList(node*& H, int* tablica) {//tworzenie listy z tych literk które s¹ nie zerowe
    for (int i = 254; i >= 0; i--) {
        if (tablica[i] != 0) {
            addToList(H, tablica[i], i);
        }
    }
}

node* findSmallestPointer(node* H) {
    node* min = NULL;
    if (H != NULL) {
        node* p = H;
        min = H;
        while (p != NULL) { // dopuki nie dojdziemy do koñæa
            if (p->val < min->val) { //jesli warunek spelnion 
                min = p;
            }
            p = p->next; //tu idziemy dalej
        }
    }
    return min;
}

node* findSecondSmallestPointer(node* H) {
    node* min = findSmallestPointer(H);//¿eby nie znaleŸæ drugi raz tego smaego wskaznika
    node* min2 = NULL;
    if (H != NULL) {
        node* p = H;
        while (p != NULL) { //prypadke jak mamy na liœcie dwie rzeczy
            if (p != min) {
                min2 = p; //odrazu przypisujemy pierwsz¹ rzeczy, bo inaczej nei zd¹¿ymy
            }
            p = p->next;
        }
        p = H;
        while (p != NULL) {
            if (p->val < min2->val && p != min) { //najpierw poronwujemy wartoœci, a  potem porónujemy wskazniki i sprawdzamyczy ju¿ nie jset przypisany do mininalnegi
                min2 = p;
            }
            p = p->next;
        }
    }
    return min2;
}

void deleteNode(node*& H) {
    if (H != NULL) {
        node* p = H;
        node* pr = H->par;
        H->par->next = H->next;
        H = H->next;
        if (H != NULL) {
            H->par = pr;
        }

        delete p;
    }
}



#define COUNT 10
void print2DUtil(tree* root, int space)
{
    // Base cases
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->R, space);

    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->val << "\n";

    // Process left child
    print2DUtil(root->L, space);
}

// Wrapper over print2DUtil()
void print2D(tree* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

node* Huffman(node*& H) {
    while (H->next != NULL) { //doóki lista sie nei skoñczy
        node* s1 = findSmallestPointer(H);
        node* s2 = findSecondSmallestPointer(H);
        tree* t = new tree; //tworzymy drzewo puste (taki jakby node)
        t->val = 0; //musimy ustawiæ zero NIE null bo by wywyallao bledy 
        t->L = s1->tree; //lewe poddrzewo to poddrzewo najmniejszego 
        t->L->par = t; //zeby mozna bylo isc do góry
        t->R = s2->tree;
        t->R->par = t;// prawe poddrzewo to poddrzewo drugiego najemniejszego
      
        s1->tree = t; //pod³¹czam drzewo do listy
        s1->val += s2->val; 
        // cout << endl<< s1->val;
        deleteNode(s2);
        // cout << s1->val;
        //print2D(H->tree);
        show(H);
    }

    return H;
}

void findLeaves(tree* root, map<int, string>& mapa) {
    if (root == NULL) {
        return;
    }

    if (root->L == NULL && root->R == NULL) {
        //cout << root->val << " " << root->par->val << endl;
        tree* p = root;
        string str = "";
        while (p->par != NULL) {
            if (p->par->L == p) {
                str = "0" + str;
            }
            else {
                str = "1" + str; //jak cos ddoaje siê od przodu 
            }
            p = p->par; //idziemy do góry 
        }
        //cout << str << endl;
        mapa[root->val] = str;
        //cout << str << endl;
    }

    // Rekurencyjnie szukamy liœci w lewym i prawym poddrzewie
    findLeaves(root->L, mapa); //tak jak search w drzewach
    findLeaves(root->R, mapa);
}




int main() {
    string s = "DAAFDDGFDSESESFSFDDFADFDAFDAFDDFSFDSFDSFDSDXFDDFSFDFFDAFDFDXFDFDGFDGFDSDAAAASAADSASASASASASASASAAAAAAAAASASSAWASAAAAAASASASDADDSADSADSSAASAAAADSADSSDAAAAADSASADSAAAAAAAASDADSADSADSASASASSSAAAAASSADSASADSAAAAFDFESDSADSADDSADADSFFFDSDSDAAAAAA";
    //string t = "DDDDDAAAAAAA";
    int tablica[255];
    map <int, string> binary;
    node* H = NULL;
    stringToArray(s, tablica);

    for (int i = 0; i < 255; i++) {
        if (tablica[i] != 0) { //wybeiramy tylko te wartoœci inne od zera 
            cout << (char)i << i << ": " << tablica[i] << endl; //i je wypisujemy 
            binary[i];
        }
    }

    createList(H, tablica);

    show(H);
    //cout << findSmallestPointer(H)->val;
    //cout << findSecondSmallestPointer(H)->val;
    //show2(H->next->next->next->next->next->next->next);
    //cout << endl << H->next->next->tree->val;
    Huffman(H);
    show(H);
    // Huffman(H);
    // Huffman(H);

     //show(H);

    print2D(H->tree);
    findLeaves(H->tree, binary);

    for (auto& element : binary) {
        cout << (char)element.first << " : " << element.second << endl;
    }



    //cout << "H val:" << H->val;
    //cout << "H next:" << H->next->val;
    //node* s1 = findSmallestPointer(H);
    //node* s2 = findSecondSmallestPointer(H);

    //cout << s1->val;
    // cout << s2->val;


}