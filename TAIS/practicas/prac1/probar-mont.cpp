
#include "../tiposdelprofesor/ColaPrio.h"

bool menorer(const int& a, const int& b) {
    return a < b;
}

bool mayore(const int& a, const int& b) {
    return a > b;
}

int maine(int argc, char* argv[]) {
	ColaPrio<int, menorer> colamin { };
	ColaPrio<int, mayore> colamax { };
	bool seguir { true };
	int entrada { };

	while (seguir) {

	    std::cin >> entrada;

	    if(entrada > 0) {  // insertar en ambos monticulos
	        colamin.inserta(entrada);
	        colamax.inserta(entrada);

	    } else if (entrada == 0) { // mostrar por pantalla los monticulos
	        std::cout << colamin << std::endl;
	        std::cout << colamax << std::endl;

	    } else if (entrada == -1) // terminar
	        seguir = false;

	    else { // mostrar el minimo y el maximo y eliminarlos
	        std::cout << "Minimo: " << colamin.primero() << std::endl; colamin.quitaPrim();
	        std::cout << "Maximo: " << colamax.primero() << std::endl; colamax.quitaPrim();
	    }
	}

	return 0;
}
