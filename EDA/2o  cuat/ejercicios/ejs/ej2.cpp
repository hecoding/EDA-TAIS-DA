#include <iostream>

#include "Pila.h"
using namespace std;

template <class T>
void lefunc (PilaLE<T> pila) {
    PilaLE<T> aux;
    
    while (!pila.esVacia()) {
        aux.apila(pila.cima());
        pila.desapila();
    }
    
    cout << aux;
}

template <class T>
void lefuncRecursive (PilaLE<T> pila) {
    if (!pila.esVacia()) {
        T elem = pila.cima();
        pila.desapila();
        lefuncRecursive (pila);
        cout << elem;
    }
}

//template <class T>
//void lefuncRecursiveCaca (PilaLE<T>::Nodo* i) {
//    if (i == NULL) {
//        cout << "vuelta: ";
//    }
//    else {
//        lefuncRecursiveCaca (i->_sig);
//        cout << i->_elem;
//    }
//}
//
//template <class T>
//void lefuncRecursive2 (PilaLE<T> pila) {
//    lefuncRecursiveCaca (pila.cima());
//}

int main2 () {
    PilaLE<int> pila;
    pila.apila(1);
    pila.apila(2);
    pila.apila(3);
    pila.apila(4);
    
    cout << "pila inicial: " << pila << endl;
    lefuncRecursive (pila);
    
    cout << endl << "pila final: " << pila;
    
    return 0;
}

