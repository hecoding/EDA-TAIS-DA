#include "Pila.h"

void pruebas() {
	PilaLE<int> p1;
	// Inversa de la pila vacia
	p1.inversa();
	assert(p1.esVacia());
	// Inversa de la pila con un elemento
	p1.apila(3);
	p1.inversa();
	assert(p1.cima() == 3);
	cout << "La inversa de la pila con un elemento es : " << p1 << "\n";
	// Inversa pila con varios elementos
	p1.apila(2); p1.apila(1);
	cout << "Pila original: " << p1 << "\n";
	p1.inversa();
	cout << "Pila inversa: " << p1 << "\n";
	assert(p1.cima() == 3);
    
	// Vaciar una pila
	p1.vacia();
	assert(p1.esVacia());
    
	p1.apila(20); p1.apila(21); p1.apila(22); p1.apila(23);
	try {
		cout << "Nueva pila: " << p1 << "\n";
	}
	catch(...) {cout << "Es posible que no se vaciase bien la pila \n";}
    
	// Prueba de ponEncima
	p1.ponEncima(3);
	cout << "La pila no se debe haber modificado: " << p1 << "\n";
	assert(p1.cima() == 23);
	p1.ponEncima(22);
	cout << " se ha puesto encima el elemento 22 : " << p1 << "\n";
	assert(p1.cima() == 22);
	p1.ponEncima(22);
	cout << "Pone encima el elemento que ya estaba: " << p1 << "\n";
	assert(p1.cima() == 22);
	p1.ponEncima(20);
	cout << "Nueva cima el 20: " << p1 << "\n";
	assert(p1.cima() == 20) ;
    
	// Prueba de revolver
	PilaLE<char> ent;
	ent.apila('A');
	cout << "Revolver un elemento no modifica la pila " << ent << "\n";
	assert(ent.cima() == 'A');
	ent.apila('B');
	ent.revolver();
	cout << "Revolver una pila de 2 elementos: " << ent << "\n";
	assert(ent.cima() == 'A');
	ent.vacia();
	ent.apila('D'); ent.apila('C'); ent.apila('B'); ent.apila('A');
	ent.revolver();
	cout << "Resultado de revolver una pila de muchos elementos: " << ent << "\n";
	assert(ent.cima() == 'B');
    
	return;
}


int main() {
	pruebas();
	cout << "Fin de las pruebas\n";
	return 0;
}