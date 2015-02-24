#ifndef MATRICULA_H
#define MATRICULA_H

#include "Lista.h"
#include <string>

struct Matricula {
	Lista<std::string> multas;
	int t_ini;
	int t_fin;
};

#endif