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

void imprimir_resultado (const Matriz<std::size_t>& matriz) {

}

Matriz<std::size_t> ebanisto (const std::vector<std::size_t>& corte, std::size_t ja) { // ebanisto (i, j) i = cortes de 1 a i, j = longitud tronco
	Matriz<std::size_t> ebanisto_matr(corte.size(),ja);
	Matriz<std::size_t> solucion (corte.size(),ja);

	for (std::size_t m = 0; m < ebanisto_matr.numfils(); ++m) {
		for (std::size_t n = 0; n < ebanisto_matr.numcols(); ++n) {
			if (n == m + 1) // caso base ebanisto (i, i+1) = 0
				ebanisto_matr[m][n] = 0;
			else
				ebanisto_matr[m][n] = std::numeric_limits<std::size_t>::max();
		}
	}

	for (std::size_t i = corte.size() - 1; i >= 0; --i) {
		for (std::size_t j = i + 2; j <= corte.size() + 1; ++j) {
			for (std::size_t k = i + 1; k < j; ++k) {
				auto temp = ebanisto_matr[i][k] + ebanisto_matr[k][j] + 2 * (corte[j] - corte[i]);

				if (temp < ebanisto_matr[i][j]) {
					ebanisto_matr[i][j] = temp;
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

	for (auto a : problemas)
		imprimir_resultado (ebanisto(a.cortes, a.longitud));

	return 0;
}
