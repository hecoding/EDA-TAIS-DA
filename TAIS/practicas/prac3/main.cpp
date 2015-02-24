#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include "../tiposdelprofesor/Matriz.h"

class problema {
public:
	int longitud;
	std::vector<int> cortes;

	problema(int longitud, int num_cortes) : longitud { longitud } {
		cortes.reserve(num_cortes);
	}
};

std::vector<problema> lector (const std::string& ruta) {
	std::ifstream fichero (ruta);
	std::vector<problema> problemas { };
	int longitud { }, num_cortes { }, corte { };

	fichero >> longitud;

	while (longitud != 0) {
		fichero >> num_cortes;
		problema temp { longitud, num_cortes };

		temp.cortes.push_back(0); // para simplificar
		while (num_cortes != 0) {
			fichero >> corte;
			temp.cortes.push_back(corte);
			--num_cortes;
		}
		temp.cortes.push_back(longitud); // para simplificar

		problemas.push_back(temp);

		fichero >> longitud;
	}

	return problemas;
}

Matriz<int> ebanisto (const std::vector<int>& corte, const int num_cortes, int& coste_final) {
	Matriz<int> ebanisto_matr (num_cortes + 2, num_cortes + 2); // + 2 por los cortes ficticios
	Matriz<int> solucion (num_cortes + 2, num_cortes + 2); // 		que pusimos en el lector
	int coste_actual { }, menor_coste { };

	// inicializar las matrices
	for (int m = 0; m <= num_cortes + 1; ++m) {
		for (int n = 0; n <= num_cortes + 1; ++n) {
			ebanisto_matr[m][n] = 0;
			solucion[m][n] = 0;
		}
	}

	for (int i = num_cortes - 1; i >= 0; --i) {	// Recorrer en vertical (arriba a abajo)
		for (int j = i + 2; j <= num_cortes + 1; ++j) { // Recorrer en horizontal (izquierda a derecha)
			menor_coste = std::numeric_limits<int>::max();
			for (int m = i + 1; m < j; ++m) {
				coste_actual = ebanisto_matr[i][m] + ebanisto_matr[m][j] + (2 * (corte[j] - corte[i]));
				if (coste_actual < menor_coste) {
					menor_coste = coste_actual;
					solucion[i][j] = m;
				}
			}
			ebanisto_matr[i][j] = menor_coste;
		}
	}
	coste_final = menor_coste;

	return solucion;
}

void imprimir_resultado (int i, int j, const std::vector<int>& corte, const Matriz<int>& solucion) {
	int cut = solucion[i][j];

	if (cut != 0) {
		std::cout << "  ";
		std::cout << corte[cut] << std::endl;
		std::cout << "  ";
		imprimir_resultado (i, cut, corte, solucion); // recorrido en preorden. aunque la
		imprimir_resultado (cut, j, corte, solucion); // tabulación no es correcta pero es lo de menos
	}
}

int main () {
	std::string ruta = "prac3/archivos/troncos.txt";
	int coste { };

		std::vector<problema> problemas = lector(ruta);

		for (std::size_t i = 1; i <= problemas.size(); ++i) {
			problema actual = problemas[i - 1];
			std::cout << "Caso " << i << ": ";

			Matriz<int> solucion = ebanisto(actual.cortes, actual.cortes.size() - 2, coste);

			std::cout << "El coste minimo es de " << coste << "." << std::endl;
			std::cout << "Cortes: " << std::endl;
			imprimir_resultado (0, actual.cortes.size() - 1, actual.cortes, solucion);
			std::cout << std::endl;
		}

	return 0;
}
