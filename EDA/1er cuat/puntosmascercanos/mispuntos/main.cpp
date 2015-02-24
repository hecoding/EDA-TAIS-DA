/*
 * main.cpp
 *
 *  Created on: 10/12/2013
 *      Author: isabel
 */


//============================================================================
// Name        : puntoscercanos.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
using namespace std;

struct Punto {
	double x;
    double y;
};

double absolute (double x) {
	if (x < 0) return -x;
    else return x;
}

double distancia(Punto p1,Punto p2) {
	return (sqrt (double (p1.x - p2.x) * (p1.x - p2.x) + (p1.y -p2.y) * (p1.y - p2.y)));
}

double minimo(double x, double y) {
	if (x <= y) return x;
	else return y;
}

void solucionDirecta (Punto p[], int c, int f, int indY[], double& d, int& p1, int& p2) {
	double d1, d2, d3;
	
	if (f == c + 1) { // hay 2 puntos
		d = distancia(p[c], p[f]);
		if ((p[c].y) <= (p[f].y)) {
			indY[c] = c; indY[f] = f;
			p1 = c; p2 = f;
		}
		else {
			indY[c] = f; indY[f] = c;
			p1 = f; p2 = c;
		}
	}
	else if (f == c + 2) { // hay 3 puntos
		//Menor distancia y puntos que la producen
		d1 = distancia (p[c], p[c+1]); d2 = distancia (p[c], p[c+2]); d3 = distancia (p[c+1], p[c+2]);
		d = minimo (minimo (d1,d2), d3);

		if (d == d1) {p1=c;p2=c+1;}
		else if (d == d2) {p1=c;p2=c+2;}
		else {p1 = c+1; p2 = c+2;}

		// Ordenar los vectores por su componente y para tenerlo ordenado en la siguiente recursión
		// y poder rebajar el coste de hacerlo en cada llamada
        if (p[c].y<=p[c+1].y) {
            if (p[c+1].y<=p[c+2].y)
            {indY[c]=c;indY[c+1]=c+1;indY[c+2]=c+2;}
            else if (p[c].y<=p[c+2].y)
            {indY[c]=c;indY[c+1]=c+2;indY[c+2]=c+1;}
            else
            {indY[c]=c+2;indY[c+1]=c;indY[c+2]=c+1;}
        }
        else {
            if (p[c+1].y>p[c+2].y)
            {indY[c]=c+2;indY[c+1]=c+1;indY[c+2]=c;}
            else if (p[c].y>p[c+2].y)
            {indY[c]=c+1;indY[c+1]=c+2;indY[c+2]=c;}
            else
            {indY[c]=c+1;indY[c+1]=c;indY[c+2]=c+2;}
        }
	}
}

void mezclaOrdenada(Punto p[], int a, int b, int indicesY[]) {
	// En esta mezcla no se ordenan todos los puntos del vector, sólo los filtrados,
	// que vienen indicados en el parámetro indices[]
	int *auxIndices = new int[b - a + 1];
	int m = (a+b)/2;
	int i = a, j = m + 1, k = 0;

	// copiar los punteros de los puntos, ordenadamente por la coordenada y
	while ((i <= m) && (j <= b)) {
		if (p[indicesY[i]].y <= p[indicesY[j]].y) { auxIndices[k] = indicesY[i]; i = i + 1;}
		else { auxIndices[k]=indicesY[j]; j=j+1;}
		k = k + 1;
	}

	// copiar los sobrantes
	while (i <= m) {
		auxIndices[k] = indicesY[i]; i = i+1; k = k+1;
	}

	// copiar los sobrantes
	while (j <= b) {
		auxIndices[k] = indicesY[j]; j = j+1; k = k+1;
	}

	for (k = a; k <= b; k++) indicesY[k] = auxIndices[k - a] ;
	delete []auxIndices;
}

void parMasCercano(Punto p[], int c, int f, int indicesY[], double &d, int &p1, int &p2){
	int tamano = f - c + 1;
	if (tamano < 4) solucionDirecta (p, c, f, indicesY, d, p1, p2);
	else {
		int m = (c + f) / 2;

		double dIzq, dDer;
		int p1Izq, p1Der, p2Izq, p2Der;
		parMasCercano (p, c, m, indicesY, dIzq, p1Izq, p1Der);
		parMasCercano (p, m+1, f, indicesY, dDer, p2Izq, p2Der);

		// Determinamos la distancia más cercana de las dos subnubes
		if (dIzq <= dDer) {
			d = dIzq;
			p1 = p1Izq; p2 = p1Der;
		}
		else {
			d = dDer;
			p1 = p2Izq; p2 = p2Der;
		}
		
		// Contruir un array (tira vertical) con los puntos (punteros a puntos) de distancia < d con la vertical
		int *indicesYFiltrado = new int[tamano]; // como máximo, la lista después de filtrar tiene "tamano" puntos
		int contadorFiltrado = 0;
		for (int i = c; i <= f; i++) {
		    if (absolute (p[indicesY[i]].x - p[m].x) <= d) { // se accede en orden de y para tener ordenado el indicesYFiltrado 
				indicesYFiltrado[contadorFiltrado] = indicesY[i];
				contadorFiltrado++;
			}
		}

		// Mezcla ordenada por la y (esto lo he cambiado, antes estaba encima de construir el array,
		// pero si ordenamos aquí, sólo trabajamos con el array filtrado en vez de la lista entera de puntos)
		mezclaOrdenada (p, 0, contadorFiltrado - 1, indicesYFiltrado);

		// Iteración que recorre cada punto del vector filtrado y lo compara con los demás para calcular la menor distancia
		// Parece fuerza bruta (O(n^2)) pero al sólo dar 7 vueltas el bucle interno (transparencias), tiene coste lineal.
		// El vector tiene informacion hasta la posicion contadorFiltrado
		int i = 0, j;
		while ((i != f - c + 1) && (i != contadorFiltrado)) {
		    int count = 1; j = i + 1;

		    while ((j < f - c + 1) && (j != contadorFiltrado) && (count <= 7)) {
				// Calcular la distancia de un punto a otro
		        double dAux = distancia (p[indicesYFiltrado[i]], p[indicesYFiltrado[j]]);
				// Comparar distancia
		        if (dAux < d) {
					d = dAux;
					p1 = indicesYFiltrado[i]; p2 = indicesYFiltrado[j];
				}
		        count++; j++;
		    }

		    i++;
		}

		delete [] indicesYFiltrado;
	}
}

int main() {
	int numPuntos;
	// prueba automática
	/*Punto v[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}, {2, 5}, {3, 30}, {23, 64}, {5, 10},
				{13, 9}, {32, 4}, {46, 3}, {11, 30}, {5, 5}, {9, 4}, {13, 6}, {1, 8}, {6, 31}, {2, 6},
				{21, 4}, {45, 35}, {33, 9}, {12, 23}, {35, 72}, {3, 4}, {7, 81}, {95, 3}, {35, 8}, {26, 84},
				{4, 2}, {25, 76}}; numPuntos = 32;*/
	
	cout << "Número de puntos: ";
	cin >> numPuntos;
	cout << endl;
	Punto *v = new Punto[numPuntos];

	Punto p;
	for (int i = 0; i < numPuntos; i++) {
		cout << "Punto " << i + 1 << endl;
		cout << " x: ";
		cin >> p.x; 
		cout << " y: ";
		cin >> p.y;

		v[i] = p;
	}
	
	// Este vector de índices se lleva por lo mismo que se usaban los acumuladores,
	// si tenemos que ordenar el vector de Y's en cada llamada recursiva, tenemos O(n(log n)^2),
	// mientras que si lo llevamos ordenado de las anteriores llamadas recursivas, este coste se reduce a O(nlogn)
	int *indicesY = new int[numPuntos];
	double d; int p1; int p2;

	parMasCercano (v, 0, numPuntos - 1, indicesY, d, p1, p2);
	cout << "La distancia mínima es: " << d << endl;
	cout << "Entre los puntos " << p1 << " y " << p2;
	
	delete []indicesY;
	return 0;
}


// estos dos trozos de código hacen lo mismo, solo que de diferente forma (en el algoritmo viene el segundo):
// FILTRAR ANTES DE ORDENAR
/*
// Contruir un array (tira vertical) con los puntos (punteros a puntos) de distancia < d con la vertical
		int *indicesYFiltrado = new int[tamano]; // como máximo, la lista después de filtrar tiene "tamano" puntos
		int contadorFiltrado = 0;
		for (int i = c; i <= f; i++) {
		    if (absolute (p[indicesY[i]].x - p[m].x) <= d) { // se accede en orden de y para tener ordenado el indicesYFiltrado 
				indicesYFiltrado[contadorFiltrado] = indicesY[i];
				contadorFiltrado++;
			}
		}

		// Mezcla ordenada por la y (esto lo he cambiado, antes estaba encima de construir el array,
		// pero si ordenamos aquí, sólo trabajamos con el array filtrado en vez de la lista entera de puntos)
		mezclaOrdenada (p, 0, contadorFiltrado - 1, indicesYFiltrado);
*/

// ORDENAR Y DESPUÉS FILTRAR
/*
// Mezcla ordenada por la y
		mezclaOrdenada (p, c, f, indicesY);
		
		// Contruir un array (tira vertical) con los puntos (punteros a puntos) de distancia < d con la vertical
		int *indicesYFiltrado = new int[tamano]; // como máximo, la lista después de filtrar tiene "tamano" puntos
		int contadorFiltrado = 0;
		for (int i = c; i <= f; i++) {
		    if (absolute (p[i].x - p[m].x) <= d) {
				indicesYFiltrado[contadorFiltrado] = indicesY[i];
				contadorFiltrado++;
			}
		}
*/