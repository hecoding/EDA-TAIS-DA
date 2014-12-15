#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Grafo.h"

void sumar1 (std::size_t& n) {
	if (n == 9)
		n = 0;
	else
		++n;
}

void restar1 (std::size_t& n) {
	if (n == 0)
		n = 9;
	else
		--n;
}

void meter_comb (std::vector<std::size_t> numeros, std::vector<std::size_t>& combinaciones, std::size_t num_ruedas) {
	std::size_t num = 0;

	for (std::size_t i = num_ruedas; i > 0; --i) {
		num += numeros.back() * std::pow(10, i - 1);
		numeros.pop_back();
	}

	combinaciones.push_back(num);
}

std::vector<std::size_t> generar_combinaciones (std::size_t num, std::size_t num_ruedas) {
	std::vector<std::size_t> combinaciones, temp;

	// divide cada "rueda" de la combinación
	for (std::size_t i = 0; i < num_ruedas; ++i) {
		temp.push_back(num % 10);
		num /= 10;
	}

	// genera las 2 * num_ruedas combinaciones posibles, dependiendo de la configuración de las ruedas
	std::vector<std::size_t>::iterator it = temp.begin();
	while (it != temp.end()) {
		sumar1(*it);
		meter_comb(temp, combinaciones, num_ruedas);
		restar1(*it);

		restar1(*it);
		meter_comb(temp, combinaciones, num_ruedas);
		sumar1(*it);

		++it;
	}

	return combinaciones;
}

bool es_combinacion_prohibida (std::size_t combinacion, std::vector<std::size_t> prohibidos) {
	// me remito al comentario del main
	std::vector<std::size_t>::iterator resultado = std::find(prohibidos.begin(), prohibidos.end(), combinacion);

	return resultado != prohibidos.end(); // si no lo encuentra devuelve un iterador al final
}

Grafo construir_grafo (std::size_t num_ruedas, std::vector<std::size_t>& confs_prohibidas) {
	std::size_t num_vertices = std::pow(10, num_ruedas);
	Grafo problema (num_vertices);

	for (std::size_t i = 0; i < num_vertices; ++i) {
		if (!es_combinacion_prohibida(i, confs_prohibidas)) { // si está prohibida no puede tener adyacentes
			std::vector<std::size_t> combinaciones = generar_combinaciones (i, num_ruedas);
			std::vector<std::size_t>::iterator it_combinaciones = combinaciones.begin(); // un iterador permite desacoplar el recorrido del contenedor

			while (it_combinaciones != combinaciones.end()) {
				if (!es_combinacion_prohibida (*it_combinaciones, confs_prohibidas))
					problema.ponArista (i, *it_combinaciones);

				++it_combinaciones;
			}
		}
	}

	return problema;
}

std::size_t leer_numero (std::ifstream& fichero, std::size_t num_ruedas) {
	std::size_t num = 0;
	std::size_t temp = 0;

	for (std::size_t i = num_ruedas; i > 0; --i) {
		fichero >> temp;
		num += temp * std::pow(10, i - 1);
	}

	return num;
}

int main () {
	// TODO comentar cosillas no claras
	// TODO poner consts y referencias
	// TODO iteradores en vez de .at(i)
	// TODO poner input.txt en el fichero
	const std::size_t NUM_RUEDAS = 4;
	std::ifstream fichero ("prac2/archivos/casos.txt");
	std::size_t num_problemas;

	fichero >> num_problemas;
	for(std::size_t a = 0; a < num_problemas; ++a) {
		std::size_t conf_inicial, conf_final;
		conf_inicial = leer_numero(fichero, NUM_RUEDAS);
		conf_final = leer_numero(fichero, NUM_RUEDAS);

		std::size_t num_confs_prohibidas;
		/* como vamos a buscar combinaciones concretas, si el número de combinaciones prohibidas
		 * fuera mayor de 10000 convendría usar un std::vector<bool> (el estándar ha especializado
		 * este caso concreto como un bitset teniendo en mente este tipo de tareas), y si el número
		 * de combinaciones fuera mayor de mil millones lo mejor sería usar un std::unordered_set
		 * (que está implementado como un hash_set) o quizá un std::set.
		 */
		std::vector<std::size_t> confs_prohibidas;
		fichero >> num_confs_prohibidas;
		confs_prohibidas.reserve(num_confs_prohibidas); // optimización de memoria para problemas grandes

		for (std::size_t i = 0; i < num_confs_prohibidas; ++i)
			confs_prohibidas.push_back(leer_numero(fichero, NUM_RUEDAS));

		Grafo problema = construir_grafo (NUM_RUEDAS, confs_prohibidas);
		// Usamos BFS porque al contrario que DFS, nos garantiza el camino más corto
		BreadthFirstPaths busqueda (problema, conf_inicial);

		if (!busqueda.hasPathTo(conf_final))
			std::cout << "-1" << std::endl;
		else
			std::cout << busqueda.distance(conf_final) << std::endl;
	}

	return 0;
}
