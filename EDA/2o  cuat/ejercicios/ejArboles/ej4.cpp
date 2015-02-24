/* 
 * File:   ej4.cpp
 * Author: Héctor
 *
 * Created on 6 de mayo de 2014, 4:27
 */

#include <iostream>
#include "Arbin.h"
#include "Lista.h"

using namespace std;

template <typename T>
void printArbol (const Arbin<T>& arbol) {
            if (arbol == NULL) cout << "<vacío>" << endl;
            else if (arbol.esHoja()) cout << arbol.raiz() << endl;
            else if (arbol.hijoIz() != NULL || arbol.hijoDr() != NULL) {
                cout << arbol.raiz() << endl;
                cout << "   "; printArbol (arbol.hijoIz());
                cout << "   "; printArbol (arbol.hijoDr());
            }
 }

int maine() {
    // Recorrido en inorden del arbol a construir
    Lista<int> inl;
    inl.ponDr(4);inl.ponDr(2);inl.ponDr(8);inl.ponDr(5);inl.ponDr(1);inl.ponDr(9);inl.ponDr(6);inl.ponDr(3);inl.ponDr(7);
    // Recorrido en preorden del arbol a construir
    Lista<int> prel;
    prel.ponDr(1);prel.ponDr(2);prel.ponDr(4);prel.ponDr(5);prel.ponDr(8);prel.ponDr(3);prel.ponDr(6);prel.ponDr(9);prel.ponDr(7);
    Arbin<int> a(inl, prel);
    
    //printArbol(a);
        
    return 0;
}

