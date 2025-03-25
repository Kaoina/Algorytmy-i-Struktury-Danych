#include <iostream>
using namespace std;
#define COUNT 10

struct Node {
    int value;
    int balance;
    Node* parent;
    Node* left;
    Node* right;
};

void AddBST(Node*& root, int xval, Node* parent = NULL) { //wska�nik na parenta, kt�remu 
    //na pocz�tku przypisujemy nulla dla roota a w nat�pnch wywo�aniach b�dzie ta warto�� zast�pwoana innymi wska�nikami 

    if (root == NULL) {
        Node* p = new Node;
        p->value = xval;
        p->right = NULL;
        p->left = NULL;
        p->parent = parent;
        root = p;
    }
    else if (root->value > xval) {
        AddBST(root->left, xval, root);
    }
    else {
        AddBST(root->right, xval, root);
    }

}
void Show(Node*& root) {
    if (root->left != NULL) {
        Show(root->left);
    }
    cout << root->value << ">";
    if (root->right != NULL) {
        Show(root->right);
    }
}


Node* FindValue(Node* root, int value) {
    if (value == root->value) {
        return root;
    }
    else if (value < root->value) {
        FindValue(root->left, value);
    }
    else
    {
        FindValue(root->right, value);
    }
}

Node* Min(Node*& root) {
    if (root->left != NULL) {
        Min(root->left);
    }
    return root;
}
Node* Max(Node*& root) {
    if (root->right != NULL) {
        return Max(root->right);
    }
    return root;
}

Node* FindNext(Node*& root) {

    Node* p = NULL;
    if (root->right != NULL) {
        p = Min(root->right); //minimum prawego syna to b�dzie nasze suzkane
        cout << p->value << endl;
    }
    else { //nat�pnikiem jak nie ma prawego syna b�dzie pierwszy moment jak spinamy si� w prawo do g�ry 
        p = root->parent;
        Node* e = root;
        while (p != NULL && e == p->right) {
            p = p->parent;
            e = e->parent;
        }
        if (p == NULL) {
            cout << "Nastepnik nie istnieje" << endl;
        }
        else {
            cout << p << endl;
        }
    }
    return p;
}
Node* FindPrevious(Node*& root) {
    Node* p = NULL;
    if (root->left != NULL) { //je�li mamy lewego syna to poprzedikiem zawsze be�dzie popsrotu najwieksza wrato�� poddrzewa tego lewego syna
        p = Max(root->left);
        cout << p->value << endl;
    }
    else { //je�li nie istnieje lewy syn to musimy szuka� u g�ry 
        p = root->parent; //p to nasz wska�nik na rodzica
        Node* e = root;  //e to elemnt na kt�rym jeste�my 
        while (p != NULL && e == p->left) { ///p rozne od nula zeby nie wyj�� z calego drzewa 
            //dop�ki e nie b�dzie lewym synem to b �dziem sie przes�wa� w g�re i szuka�
            //pierwszy na prawo b�dze nast�nikiem
            p = p->parent; //przesuwamy wsyzstko
            e = e->parent;
        }
        if (p == NULL) {
            cout << "Poprzednik nie istnieje" << endl;
        }
        else {
            cout << p << endl; //je�li wywalilo to p jest ustawione na nastepnika 
        }
    }
    return p;
}
//nie moje(ale rozumiem)
void RotateLL(Node*& root) { 
    Node* A = root;
    Node* B = root->left;
    Node* C = root->left->left;

    A->left = NULL;
    if (B->right != NULL)
    {
        A->left = B->right;
        B->right->parent = A;
    }

    B->right = A;
    A->parent = B;

    B->left = C;
    C->parent = B;

    root = B;
}
void RotateLR(Node*& root) {
    Node* A = root;
    Node* B = root->left;
    Node* C = root->left->right;

    B->right = NULL;
    if (C->left != NULL) {
        B->right = C->left;
        C->left->parent = B;
    }

    A->left = NULL;
    if (C->right != NULL) {
        A->left = C->right;
        C->right->parent = A;
    }

    C->left = B;
    B->parent = C;

    C->right = A;
    A->parent = C;

    root = C;
}
void RotateRR(Node*& root) {
    Node* A = root;
    Node* B = root->right;
    Node* C = root->right->right;

    A->right = NULL;
    if (B->left != NULL) {
        A->right = B->left;
        B->left->parent = A;
    }

    B->left = A;
    A->parent = B;

    B->right = C;
    C->parent = B;

    root = B;
}
void RotateRL(Node*& root) {
    Node* A = root;
    Node* B = root->right;
    Node* C = root->right->left;

    B->left = NULL;
    if (C->right != NULL) {
        B->left = C->right;
        C->right->parent = B;
    }

    A->right = NULL;
    if (C->left != NULL) {
        A->right = C->left;
        C->left->parent = A;
    }

    C->right = B;
    B->parent = C;

    C->left = A;
    A->parent = C;

    root = C;
}

int GetHeight(Node* root) {
    int l = 0;
    int r = 0;
    if (root->left != NULL) {
        l = GetHeight(root->left);
    }
    if (root->right != NULL)
    {
        r = GetHeight(root->right);
    }

    if (l > r) {
        return l + 1;
    }
    else
    {
        return r + 1;
    }
}
void CalculateBalance(Node* root) {
    int l = 0;
    int r = 0;
    if (root->left != NULL) {
        l = GetHeight(root->left);
    }
    if (root->right != NULL)
    {
        r = GetHeight(root->right);
    }

    root->balance = l - r;
}
void BalanceNode(Node*& root) {
    CalculateBalance(root);
    if (root->balance == -2) {
        if (root->right->balance == -1) {
            RotateRR(root);
        }
        else
        {
            RotateRL(root);
        }
    }
    else if (root->balance == 2) {
        if (root->left->balance == 1) {
            RotateLL(root);
        }
        else
        {
            RotateLR(root);
        }
    }
}
//
void AddAVL(Node*& root, int value, Node* parent = NULL) {
    if (root == NULL) {
        Node* p = new Node;
        p->value = value;
        p->left = NULL;
        p->right = NULL;
        p->parent = parent;
        root = p;
    }
    else
    {
        if (value < root->value) {
            AddAVL(root->left, value);
        }
        else
        {
            AddAVL(root->right, value);
        }
        BalanceNode(root);
    }
}
void DelValBST(Node*& root, int xval) { // usuwa eelemnty, rozparuje 3 opcjke 

    Node* p = FindValue(root, xval); //znajudjemy to co chcemy usunac
    Node* e = p->parent; //wskaznik na parent 
    if (p->value == xval) {

        if (p->right == NULL && p->left == NULL) { //1 opcja elemnt jest lisciem, warunek - lewe i prawe to null wiadomka 
            if (e->right == p) { //je�li lewy parenta to nasze p to usuwamy prawy 
                p->parent->right = NULL; //przypisujemy prawemu warto�� nula zeby sie wsyztko zgadza�o  (mo�e by� e->R)
                delete p;  //usuamy p i eleganzko 
            }
            else if (e->left == p) { //analogicznie 
                p->parent->left = NULL;
                delete p;
            }
        }
        //opcja 2 - usuwanie ojc�w li�ci
        else if (p->right != NULL && p->right->right == NULL && p->right->left == NULL) { //dwa osostanie warunki to waruni bycia ojcem lis�i 
            p->value = p->right->value; //warto�ci przepisujemy
            e = p->right; //ustawiamy wska�nik na dziecioka
            p->right = NULL; //ustawiamy po��czenie na zamiast dzieciaka to null
            delete e; //usuwamy dziecioka
        }

        else if (p->left != NULL && p->left->right == NULL && p->left->left == NULL) { // to samo ale jestesmy ojcem lewego li�cia 
            p->value = p->left->value;
            e = p->left;
            p->left = NULL;
            delete e;
        }

        else {   //3 opcja - losowe miejsce
            //plan dzia�ania
            // znajdujemy nast�nika - liczb� nas�n� co do watyo��i w drzewie
            if (p->right != NULL) { //je�li jest co� w prawo jest to napewno nast�nik bedzie i na nim dzialamy
                e = FindNext(p);
                p->value = e->value; //plan jest taki ze znajdujemy nastepnika, robimy podmianke,  a po tym usuwamy nastepnika
                if (e->right != NULL && e->parent->left == e) {//sprawdzamy czy nastepnik to lewy syn, i czy ma prawe dzieci�
                    e->parent->left = e->right; //to ma sens na kartce
                    delete e;
                }
                else if (e->right != NULL && e->parent->right == e) { //analogicznie ale odbicie lustzrane
                    e->parent->right = e->right;
                    delete e;
                }
                else { ///to nastpenik to lisc
                    e->parent->left = NULL; //cokolwiek by to nie bylo wracam do g�ry na lewo popropstu i tak ustawiamy null
                    delete e; //i suuwamy
                }
            }
            else if (p->left != NULL) { //je�li jest co� na lewo to to sie wykonuje (wtedy napewno bedzie poprzednik i na nim dzialamy)
                e = FindPrevious(p);
                p->value = e->value;
                if (e->parent->right == e && e->left != NULL) {
                    e->parent->right = e->left;
                    delete e;
                }
                else if (e->parent->left == e && e->left != NULL) {
                    e->parent->left = e->left;
                    delete e;
                }
                else {
                    e->parent->right = NULL;
                    delete e;
                }
            }
        }

    }

}

void print2DUtil(Node* root, int space)
{
    if (root == NULL)
        return;

    space += COUNT;

    print2DUtil(root->right, space);

    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->value << "\n";

    print2DUtil(root->left, space);
}
void print2D(Node* root)
{
    print2DUtil(root, 0);
    cout << "------------------------------------------" << endl;
}

int main()
{
    Node* root = NULL;
    AddAVL(root, 0);
    AddAVL(root, -8);
    AddAVL(root, -20);
    AddAVL(root, 10);
    AddAVL(root, -5);
    AddAVL(root, -6);
    AddAVL(root, 15);
    AddAVL(root, 20);
    AddAVL(root, 45);
    AddAVL(root, -2);
    AddAVL(root, -36);
    AddAVL(root, 18);
    AddAVL(root, -7);
    print2D(root);
  
}