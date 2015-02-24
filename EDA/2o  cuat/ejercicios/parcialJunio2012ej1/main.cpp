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

Nodo* fun (Nodo* n, int clave, bool& claveEncontrada) {
	if (n == NULL) return NULL;
	else {
		Nodo* iz = fun (n->_iz, clave, claveEncontrada);
		if (iz != NULL) return iz;
		if (claveEncontrada)
			if (n->_clave > clave) return n;
		Nodo* dr = fun (n->_dr, clave, claveEncontrada);
		if (dr != NULL) return dr;

		if (n->_clave == clave) {
			claveEncontrada = true;
			if (n->_dr != NULL) return fun (n->_dr, clave, claveEncontrada);
			else return NULL;
		}
		else return NULL;
	}
}

static void inordenAcu(Nodo* ra) {
	if (ra == NULL) return;

	inordenAcu(ra->_iz);
	cout << ra->_valor << " ";
	inordenAcu(ra->_dr);
}

// función que encuentra la siguiente clave mayor que la dada en un arbol, recursivamente sin usar iteradores ni estructuras auxiliares
int main() {
	int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	int N = 15;
	int i = 0, j = N;
	
	Nodo* n = construye(v, i, j);

	bool claveEncontrada = false;
	
	inordenAcu(n); cout << endl;
	int clave; cin >> clave;

	Nodo* res = fun (n, clave, claveEncontrada);

	if (res == NULL) cout << "no hay clave más grande que " << clave;
	else
		cout << res->_clave;

	return 0;
}