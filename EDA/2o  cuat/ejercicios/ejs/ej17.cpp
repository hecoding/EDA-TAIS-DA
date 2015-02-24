#include <iostream>
#include "Lista.h"
using namespace std;

template <class T>
const Lista<T> coso (const Lista<T> lista1, const Lista<T> lista2) {
    Lista<T> resultado;
    int acarreo = 0;
    Lista<T>::IteradorInverso it1 = lista1.principioInverso();
    Lista<T>::IteradorInverso it2 = lista2.principioInverso();
    
    while (it1 != lista1.finalInverso() && it2 != lista2.finalInverso()) {
        T temp = it1.elem() + it2.elem();
        resultado.ponDr ((temp % 10) + acarreo);
        acarreo = temp / 10;
        
        it1.avanza();
        it2.avanza();
    }
    
    while (it1 != lista1.finalInverso()) {
        resultado.ponDr ((it1.elem() + acarreo) % 10);
        acarreo = (it1.elem() + acarreo) / 10;
        it1.avanza();
    }
    
    if (it2 != lista2.finalInverso()) {
        resultado.ponDr ((it2.elem() + acarreo) % 10);
        acarreo = (it2.elem() + acarreo) / 10;
        it2.avanza();
    }
    
    return resultado;
}

int main () {
    Lista<int> lista1;
    Lista<int> lista2;
    lista1.ponDr(3);
    lista1.ponDr(2);
    lista1.ponDr(4);
    lista1.ponDr(8);
    lista2.ponDr(4);
    lista2.ponDr(5);
    lista2.ponDr(0);
    
    cout << lista1 << endl << lista2 << endl;
    Lista<int> result = coso (lista1, lista2);
    cout << result;
    
    return 0;
}