#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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

Matriz<std::size_t> ebanisto (std::size_t i, std::size_t j) {
	Matriz<std::size_t> ebanisto_matr(i,j);
	Matriz<std::size_t> cortes(i,j);

	for (std::size_t m = 0; m < ebanisto_matr.numfils(); ++m) {
		for (std::size_t n = 0; n < ebanisto_matr.numcols(); ++n)
			ebanisto_matr[m][n] = 0;
			cortes[m][n] = 0;
	}

	for (std::size_t d = 1; d < ebanisto_matr.numcols() - 1; ++d) {
		for (std::size_t i = 1; i < ebanisto_matr.numfils() - d; ++i) {
			std::size_t j = i + d;
			for (std::size_t k = i + 1; i < j; ++k) {
				auto temp = ebanisto_matr[i][k] + ebanisto_matr[k][i] + 2 * (v[j] - v[i]);

				if (temp < ebanisto_matr[i][j]) {
					ebanisto_matr[i][j] = temp;
					cortes[i][j] = k;
				}
			}
		}
	}

	return cortes;
}


int main () {
	std::string ruta = "prac3/archivos/troncos.txt";

	std::vector<problema> problemas = lector(ruta);

	for (auto a : problemas)
		imprimir_resultado (ebanisto(a.cortes.size(), a.longitud));

	return 0;
}
