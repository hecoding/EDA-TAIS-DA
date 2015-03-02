#include <iostream>

#include "../ejLineales2/Lista.h"
#include "../ejLineales2/Pila.h"
using namespace std;

template <class T>
void fun(PilaLE<T>& pila, int n) {
    Lista<T> l;
    int i = 0;
    
    while (i < n && !pila.esVacia()) {
        l.ponDr(pila.cima());
        pila.desapila();
        i++;
    }
    
    i = 0;
    while (i < n && !l.esVacia()) {
        pila.apila(l.primero());
        l.resto();
        i++;
    }
}

int main7() {
    PilaLE<int> pila;
    pila.apila(1);
    pila.apila(2);
    pila.apila(3);
    pila.apila(4);
    
    cout << pila << endl;
    
    fun (pila, 3);
    
    cout << pila << endl;
    
    return 0;
}

