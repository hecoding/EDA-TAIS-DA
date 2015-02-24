#include <iostream>
#include "Complejo.h"
#include "ExcepcionTAD.h"
using namespace std;

int main() {
    
	Complejo<float> c1(3.6,2.4);
	Complejo<float> c2(1.5,1.8);
    
	Complejo<double> c3(3.6,-2.4);
	Complejo<double> c4(-1.5,0);
    
	Complejo<double> c5(3.6,-2.4);
	Complejo<double> c6(3.6,-2.4);
	if (c5 == c6)
	    cout << "Son iguales " << endl;
	else
		cout << "Son distintos " << endl;
	Complejo<double> c7;
	c7 = c5 + c6;
	cout << "Parte real de c5 + c6: " << c7.getReal() << endl;
	cout << "Parte imaginaria de c5 + c6: " << c7.getImaginario() << endl;
    
	try {
		Complejo<float> c8(0,0);
		c1 = c1 / c8;
		cout << "No hay error " << endl;
	}
	catch (ExcepcionTAD e) {cout << e.getCausa() << endl;}
    
	return 0;
}