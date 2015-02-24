#include <iostream>
#include <fstream>
#include "ColaMedianas.h"

using namespace std;

bool menore(const int& a, const int& b) {
	return a < b;
}

bool mayor(const int& a, const int& b) {
	return a > b;
}


int mainColaMedianas(int argc, char* argv[]) {

	ColaMedianas<int, menore, mayor> cm;

	ifstream fichero("prac1/archivos/input1.txt");
	ofstream ficheroSal("prac1/archivos/output1.txt");
	int v;

	while(fichero >> v){
		if (v >= 0) {
			cm.inserta(v);
		} else {
			int med = cm.mediana();
			cm.quitaMediana();
			ficheroSal << med << endl;
		}
	}

	fichero.close();
	ficheroSal.close();

	return 0;
}

