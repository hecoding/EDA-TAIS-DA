#include <iostream>
using namespace std;

typedef struct {
	int x;
	int y;
} Punto;

void hacerSitio (Punto v[], int n, int k) {
	
}

void imprimir (Punto v[], int n) {
	for (std::size_t i = 0; i < n; ++i)
		cout << v[i].x << " ";

	cout << endl;
}

void ordInsercion (Punto v[], int c, int f) {
	/*
	int tamano = f - c + 1;

	for (size_t i = 0; i < tamano; ++i) {
		size_t j = 0;
		bool puesto = false;
		while (j < tamano && !puesto) {
			if (v[j].x <= v[i].x) {
				std::swap (v[i], v[j]);
				puesto = true;
			}
			else
				j++;
		}
		puesto = false;
	}*/
}

int mMedianas (Punto v[], int c, int f) {
	int tamano = f - c + 1;

	if (tamano <= 12) {
		ordInsercion (v, c, f);
		return (c + f) / 2;
	}
	else {
		int s = tamano / 5;
		int posibleM;
		Punto aux;

		for (size_t i = 0; i < s; i++) {
			ordInsercion (v, c + 5*i, f + 5*i);
			posibleM = ((c + 5 * i) + (f + 5 * i)) / 2;
			aux = v[c + i]; v[c + i] = v[posibleM]; v[posibleM] = aux;
		}
		int mm = mMedianas (v, 0, s - 1);
		return mm;
	}
}

int miin () {
	Punto v[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}, {2, 5}, {3, 30}, {23, 64}, {5, 10},
				{13, 9}, {32, 4}, {46, 3}, {11, 30}, {5, 5}, {9, 4}, {13, 6}, {1, 8}, {6, 31}, {2, 6},
				{21, 4}, {45, 35}, {33, 9}, {12, 23}, {35, 72}, {3, 4}, {7, 81}, {95, 3}, {35, 8}, {26, 84},
				{4, 2}, {25, 76}};
	Punto vec[] = {{1, 0}, {2, 0}, {4, 0}, {5, 0}, {3, 0}};
	imprimir (vec, 5);

	mMedianas (vec, 0, 5 - 1);

	imprimir (vec, 5);

	return 0;
}