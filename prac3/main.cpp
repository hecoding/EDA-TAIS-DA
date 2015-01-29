#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include "Matriz.h"

class problema {
public:
	std::size_t longitud;
	std::vector<std::size_t> cortes;

	problema (std::size_t longitud, std::size_t num_cortes) : longitud (longitud) {
		cortes.reserve(num_cortes);
	}
};

std::vector<problema> lector (const std::string& ruta) {
	std::ifstream fichero (ruta);
	std::vector<problema> problemas;
	std::size_t longitud, num_cortes, corte;

	fichero >> longitud;

	while (longitud != 0) {
		fichero >> num_cortes;
		problema temp (longitud, num_cortes);

		while (num_cortes != 0) {
			fichero >> corte;
			temp.cortes.push_back(corte);
			--num_cortes;
		}

		problemas.push_back(temp);

		fichero >> longitud;
	}

	return problemas;
}

void imprimir_resultado (int i, int j, const std::vector<std::size_t>& cortes, const Matriz<std::size_t>& matriz) {
	int corte = matriz[i][j];
	if (corte != 0) {
		std::cout << cortes[corte] << std::endl;
		imprimir_resultado (i, corte, cortes, matriz);
		imprimir_resultado (corte, j, cortes, matriz);
	}
}

Matriz<std::size_t> ebanisto (const std::vector<std::size_t>& corte, std::size_t ja) { // ebanisto (i, j) i = cortes de 1 a i, j = longitud tronco
	Matriz<std::size_t> ebanisto_matr(corte.size(),ja); // poner num cortes en ja
	Matriz<std::size_t> solucion (corte.size(),ja); // poner num cortes en ja
	std::size_t corte_actual, menor_corte;

	// inicializar las matrices
	for (std::size_t m = 0; m < corte.size(); ++m) {
		for (std::size_t n = 0; n < ja; ++n) { // poner num cortes en ja
			ebanisto_matr[m][n] = 0;
			solucion[m][n] = 0;
		}
	}

	// recorremos de arriba a abajo y de izquierda a derecha
	for (int i = corte.size() - 1; i >= 0; --i) {
		for (int j = i; j < corte.size(); ++j) {
			menor_corte = std::numeric_limits<std::size_t>::max();

			for (int k = i; k < j; ++k) {
				corte_actual = ebanisto_matr[i][k] + ebanisto_matr[k][j] + 2 * (corte[j] - corte[i]);

				if (corte_actual < menor_corte) {
					ebanisto_matr[i][j] = menor_corte = corte_actual;
					solucion [i][j] = k;
				}
			}

		}
	}

	return solucion;
}


int main () {
	std::string ruta = "prac3/archivos/troncos.txt";

	std::vector<problema> problemas = lector(ruta);

	for (std::size_t i = 1; i <= problemas.size(); ++i) {
		problema actual = problemas[i - 1];
		Matriz<std::size_t> solucion = ebanisto(actual.cortes, actual.longitud);
		std::cout << "Caso " << i << ": El coste mínimo es de " << solucion[0][actual.longitud - 1] << "." << std::endl; // o poner size,size
		std::cout << "Cortes: " << std::endl;
		imprimir_resultado (0, problemas.size(), actual.cortes, solucion);
	}

	return 0;
}
