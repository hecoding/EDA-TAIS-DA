#ifndef TRAMO_H
#define TRAMO_H

#include <string>

struct Tramo {
	std::string camaraInicial;
	std::string camaraFinal;
	int tiempo_min;
	Lista<std::string> multados;
};

#endif