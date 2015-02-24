#include <iostream>

#include "Arbin.h"
using namespace std;

template <typename T>
bool esOrdenadoAux(const Arbin<T>& a, T* min, T* max) {
    return false;
}

template <typename T>
bool esOrdenado(const Arbin<T>& a) {
    return esOrdenadoAux(a, NULL, NULL);
}

int main() {
    // Recorrido en preorden del arbol a construir
    Lista<int> prel;
    prel.ponDr(4);prel.ponDr(2);prel.ponDr(1);prel.ponDr(3);prel.ponDr(6);prel.ponDr(5);
    //inorden
    Lista<int> inl;
    inl.ponDr(1);inl.ponDr(2);inl.ponDr(3);inl.ponDr(4);inl.ponDr(5);inl.ponDr(6);
    Arbin<int> a(inl, prel);
    
    if (esOrdenado(a)) cout << "Ordenado";
    else cout << "No ordenado";

    return 0;
}

