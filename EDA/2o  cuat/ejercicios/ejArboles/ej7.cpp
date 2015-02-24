/* 
 * File:   ej7.cpp
 * Author: Héctor
 *
 * Created on 7 de mayo de 2014, 1:00
 */

#include <iostream>
#include "Arbin.h"

using namespace std;

template <typename T>
bool homogeneo (const Arbin<T>& arbol) {
    if (arbol.esHoja()) return true;
    else if (arbol.hijoIz()== NULL || arbol.hijoDr() == NULL)
        return false;
    else return homogeneo (arbol.hijoIz()) && homogeneo (arbol.hijoDr());
    
}

int mainee() {
    Lista<int> inl;
    inl.ponDr(4);inl.ponDr(2);inl.ponDr(8);inl.ponDr(5);inl.ponDr(1);inl.ponDr(9);inl.ponDr(6);inl.ponDr(3);inl.ponDr(7);
    // Recorrido en preorden del arbol a construir
    Lista<int> prel;
    prel.ponDr(1);prel.ponDr(2);prel.ponDr(4);prel.ponDr(5);prel.ponDr(8);prel.ponDr(3);prel.ponDr(6);prel.ponDr(9);prel.ponDr(7);
    Arbin<int> a(inl, prel);
    
//    if (homogeneo(a))
//        cout << "Es homogéneo";
//    else
//        cout << "No es homogéneo";

    return 0;
}

