#include <iostream>

using namespace std;

const int M = 5, N = 8;
const char PALABRA[] = {'E', 'D', 'A'};

typedef enum {
	norte, sur, este, oeste
} direccion;

typedef struct {
	int x;
	int y;
} posicion;

// FUNCIONES DE AZÚCAR
void imprimirCasillas (char casillas[][N]) {
	cout << "   ";
	for (int k = 0; k < N; k++) cout << k << ": "; cout << endl;
	for (int i = 0; i < M; i++) {
		cout << i << ": ";
		for (int j = 0; j < N; j++)
			cout << casillas[i][j] << "  ";
		cout << endl;
	}
}

char enumAChar (direccion dir) {
	switch (dir) {
	case norte: return 'N'; break;
	case sur: return 'S'; break;
	case este: return 'E'; break;
	case oeste: return 'O'; break;
	}
}

void imprimirSolucion (direccion solucion[], int tamano) {
	cout << "Solución: ";
	for (int i = 0; i < tamano; i++) {
		cout << enumAChar(solucion[i]) << " ";
	}
}

// FUNCIONES AUXILIARES
void inicializarMarcas (bool marcas[][N]) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++)
			marcas[i][j] = false;
	}
}

direccion siguienteDireccion (int i) {
	switch (i) {
	case 0: return norte; break;
	case 1: return sur; break;
	case 2: return este; break;
	case 3: return oeste; break;
	}
}

void siguientePosicion (direccion dir, posicion &pos) {
	switch (dir) {
	case norte: pos.y++; break;
	case sur: pos.y--; break;
	case este: pos.x++; break;
	case oeste: pos.x--; break;
	}
}

void copiarVector (direccion mejorSol[], direccion sol[], int k) {
	for	(int i = 0; i <= k; i++)
		mejorSol[i] = sol[i];
}

// FUNCIONES
bool esValida (char casillas[][N], direccion dir, posicion posActual, bool marcas[][N], int letra) {
	return (posActual.x < M && posActual.y < N) && !marcas[posActual.x][posActual.y] && casillas[posActual.x][posActual.y] == PALABRA[letra];
}

bool esSolucion (posicion posActual, posicion posFinal) {
	return posActual.x == posFinal.x && posActual.y == posFinal.y;
}

void tratarSolucion (direccion sol[], int k, direccion mejorSol[], int &mejorTamano) {
	if (k < mejorTamano) {
		mejorTamano = k;
		copiarVector (mejorSol, sol, k);
	}
}

void actualizarLetra (int &letra) {
	if (letra == 2) letra = 0;
	else letra++;
}

void caminoVA (char casillas[][N], direccion sol[], int k, bool marcas[][N], posicion posActual, posicion posFinal, int letra, direccion mejorSol[], int &mejorTamano) {
	for (int i = 0; i < 4; i++) {
		sol[k] = siguienteDireccion (i);
		siguientePosicion (sol[k], posActual);

		if (esValida (casillas, sol[k], posActual, marcas, letra)) {
			if (esSolucion (posActual, posFinal))
				tratarSolucion (sol, k, mejorSol, mejorTamano);
			else {
				marcas [posActual.x][posActual.y] = true;
				actualizarLetra (letra);
				caminoVA (casillas, sol, k + 1, marcas, posActual, posFinal, letra, mejorSol, mejorTamano);
				// no hace falta desmarcar
			}
		}
	}
}

void camino (char casillas[][N], direccion solucion[], int &tamano, posicion posInicial, posicion posFinal) {
	bool marcas[M][N];
	inicializarMarcas (marcas);
	caminoVA (casillas, solucion, 0, marcas, posInicial, posFinal, 0, solucion, tamano);
}

int main () {
	char casillas[M][N] = {'M', 'D', 'A', 'A', 'E', 'E', 'D', 'A',
							'A', 'E', 'E', 'D', 'D', 'A', 'N', 'D',
							'D', 'B', 'D', 'X', 'E', 'D', 'A', 'E',
							'E', 'A', 'E', 'D', 'A', 'R', 'T', 'D',
							'E', 'D', 'M', 'P', 'L', 'E', 'D', 'A'};
	direccion solucion[M * N];
	int tamano = M * N;
	posicion posInicial, posFinal;
	int temp;

	imprimirCasillas (casillas);

	cout << "Posición inicial" << endl;
	cout << "x: "; cin >> temp; posInicial.x = temp;
	cout << "y: "; cin >> temp; posInicial.y = temp;
	cout << endl;
	cout << "Posición final" << endl;
	cout << "x: "; cin >> temp; posFinal.x = temp;
	cout << "y: "; cin >> temp; posFinal.y = temp;

	camino (casillas, solucion, tamano, posInicial, posFinal);

	imprimirSolucion (solucion, tamano);
	
	return 0;
}