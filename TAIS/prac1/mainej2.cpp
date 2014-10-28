#include <fstream>
#include <limits>
#include "ColaPrioPares.h"

using namespace std;

bool menor(const int& a, const int& b) {
	return a < b;
}

void mezcla_multiple(ifstream streams[], int N) { // ocupadas las posiciones [1..N]
	// solo nos va a hacer falta un nodo por archivo
	ColaPrioPares<int, menor> cola(N);
	int elemento, archivoProcedente;
	Par<int> parTemp;

	for (archivoProcedente = 1; archivoProcedente <= N; ++archivoProcedente) {
		streams[archivoProcedente] >> elemento;
		cola.inserta(archivoProcedente, elemento); // ordenamos por el elemento, no por el archivo de donde viene
	}

	while (!cola.esVacia()) {
		parTemp = cola.primero();
		cola.quitaPrim();
		cout << parTemp.prioridad << " "; // en realidad es el elemento

		if (streams[parTemp.elem] >> elemento)
			cola.inserta(parTemp.elem, elemento);
	}
}


int main(int argc, char* argv[]) {
	if (argc > 1) {
		ifstream *streams = new ifstream[argc];
		for (int i = 1; i < argc; i++)
			streams[i].open(argv[i]);

		mezcla_multiple(streams, argc - 1);

		for (int i = 1; i < argc; i++)
			streams[i].close();
	}

	return 0;
}
