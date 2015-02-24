#include <iostream>

#include "Pila.h"

using namespace std;

int main1() {
    int n = 64323;
    PilaLE<int> pila;
    
    while (n != 0) {
        pila.apila(n % 10);
        n /= 10;
    }
    
    int suma = 0;
    while (!pila.esVacia()) {
        suma += pila.cima();
        cout << pila.cima();
        pila.desapila();
        if (!pila.esVacia()) // unefficient shit
            cout << " + ";
    }
    cout << " = " << suma;
    
    return 0;
}

