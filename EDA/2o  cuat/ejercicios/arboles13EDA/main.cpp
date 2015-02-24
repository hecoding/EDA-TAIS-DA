#include <iostream>

using namespace std;

class Nodo {
	public:
		Nodo() : _iz(NULL), _dr(NULL) {}
		Nodo(const int &clave, const int &valor)
        : _clave(clave), _valor(valor), _iz(NULL), _dr(NULL) {}
		Nodo(Nodo *iz, const int &clave, const int &valor, Nodo *dr)
        : _clave(clave), _valor(valor), _iz(iz), _dr(dr) {}
        
		int _clave;
		int _valor;
		Nodo *_iz;
		Nodo *_dr;
};

Nodo* construye (int v[], int i, int j) {
	if (i > j) return NULL;
	else if (i == j) return new Nodo(v[i], v[i]);
	else return new Nodo (construye(v, i, (((i + j) / 2) - 1)), v[(i + j) / 2], v[(i + j) / 2], construye(v, (((i + j) / 2) + 1), j));
}

// construye un �rbol de b�squeda balanceado a partir de un vector. si este vector es el inorden de un �rbol,
// podemos meter esta funci�n en la implementaci�n din�mica del tipo �rbol de b�squeda y tenemos una funci�n
// que balancea el �rbol para que las b�squedas sean m�s r�pidas :D
int main() {
	int v[] = {1, 2, 3, 4, 5, 6, 7};
	int N = 7;
	int i = 0, j = N;

	Nodo* n = construye(v, i, j);

	return 0;
}