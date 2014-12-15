#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Grafo.h"

void sumar_ciclicamente (std::size_t& n) {
	// gira la rueda a la izquierda
	if (n == 9)
		n = 0;
	else
		++n;
}

void restar_ciclicamente (std::size_t& n) {
	// gira la rueda a la derecha
	if (n == 0)
		n = 9;
	else
		--n;
}

std::vector<std::size_t> numero_a_ruedas (std::size_t numero, std::size_t num_ruedas) {
	std::vector<std::size_t> ruedas;

	// divide cada "rueda" de la combinación
	for (std::size_t i = 0; i < num_ruedas; ++i) {
		ruedas.push_back(numero % 10);
		numero /= 10;
	}

	return ruedas;
}

std::size_t ruedas_a_numero (std::vector<std::size_t> numeros, std::size_t num_ruedas) {
	std::size_t num = 0;

	for (std::size_t i = num_ruedas; i > 0; --i) {
		num += numeros.back() * std::pow(10, i - 1);
		numeros.pop_back();
	}

	return num;
}

std::vector<std::size_t> generar_combinaciones (std::size_t num, std::size_t num_ruedas) {
	std::vector<std::size_t> combinaciones, temp;
	temp = numero_a_ruedas(num, num_ruedas);

		// genera las 2 * num_ruedas combinaciones posibles, dependiendo de la configuración de las ruedas
		for (std::vector<std::size_t>::iterator it = temp.begin(); it != temp.end(); ++it) {
		sumar_ciclicamente(*it);
		combinaciones.push_back(ruedas_a_numero(temp, num_ruedas));
		restar_ciclicamente(*it);

		restar_ciclicamente(*it);
		combinaciones.push_back(ruedas_a_numero(temp, num_ruedas));
		sumar_ciclicamente(*it);
	}

	return combinaciones;
}

bool es_combinacion_prohibida (std::size_t combinacion, std::vector<std::size_t> prohibidos) {
	// me remito al comentario del main
	std::vector<std::size_t>::iterator resultado = std::find(prohibidos.begin(), prohibidos.end(), combinacion);

	return resultado != prohibidos.end(); // si find() no lo encuentra devuelve un iterador al final
}

Grafo construir_grafo (std::size_t num_ruedas, std::vector<std::size_t>& confs_prohibidas) {
	std::size_t num_vertices = std::pow(10, num_ruedas);
	Grafo problema (num_vertices);

	for (std::size_t i = 0; i < num_vertices; ++i) {
		if (!es_combinacion_prohibida(i, confs_prohibidas)) { // si está prohibida no puede tener adyacentes
			std::vector<std::size_t> combinaciones = generar_combinaciones (i, num_ruedas);

			// un iterador permite desacoplar el recorrido del contenedor
			for (std::vector<std::size_t>::iterator it = combinaciones.begin(); it != combinaciones.end(); ++it) {
				if (!es_combinacion_prohibida (*it, confs_prohibidas))
					problema.ponArista (i, *it);
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
	// TODO poner referencias
	// TODO poner consts
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
