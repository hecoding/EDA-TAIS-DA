#include <iostream>
#include "MultaMatic.h"

using namespace std;

int main() {
	MultaMatic m;
	try {
        m.insertaTramo("AP6GuadarramaII", "AP6GuadarramaIIIni", "AP6GuadarramaIIFin",118);
        m.insertaTramo("AP6GuadarramaIII", "AP6GuadarramaIIIIni", "AP6GuadarramaIIIFin",288);
        m.insertaTramo("AP9Sartego","AP9SartegoIni","AP9SartegoFin",49);
        m.insertaTramo("A4Despenaperros","A4DespenaperrosIni","A4DespenaperrosFin",125);
        m.insertaTramo("Zaragoza","ZaragozaIni","ZaragozaFin",90);
        m.insertaTramo("A7Torrox","A7TorroxIni","A7TorroxFin",52);
        m.fotoEntrada("AP6GuadarramaIIIni", "4532DFT",2860);
        m.fotoEntrada("AP9SartegoIni", "9821NNN",2863);
        m.fotoEntrada("AP6GuadarramaIIIni", "0021BBB",2865);
        m.fotoSalida("AP9SartegoFin","9821NNN",2880); // Multado
        m.fotoSalida("AP6GuadarramaIIFin", "4532DFT",2960); // Multado
        m.fotoSalida("AP6GuadarramaIIFin", "0021BBB",2995); // No multado
        m.fotoEntrada("ZaragozaIni", "9821NNN",3856);
        m.fotoSalida("ZaragozaFin", "9821NNN",3956); // No multado
        cout << "Multas por matricula \n";
		// La sobreescritura del operador << en el TAD Lista tal como está, a mí no me funciona
        cout << "4532DFT   " << m.multasPorMatricula("4532DFT") << endl;
        cout << "0021BBB   " << m.multasPorMatricula("0021BBB") << endl;
        cout << "9821NNN   " << m.multasPorMatricula("9821NNN") << endl;
        cout << "Multas por tramo \n" ;
        cout << "AP6GuadarramaII\n";
		// El nombre Matricula lo uso para referirme a un coche y no puede ser Lista<Matricula>,
		// para una simple práctica supongo que dará igual
        Lista<string> l = m.multasPorTramos("AP6GuadarramaII");
        Lista<string>::Iterador it = l.principio();
        Lista<string>::Iterador itFinal = l.final();
        while (it != itFinal) {
            cout << it.elem();
            it.avanza();
        }
        cout << endl;
        cout << "AP6GuadarramaIII\n";
        l = m.multasPorTramos("AP6GuadarramaIII");
        it = l.principio();
        itFinal = l.final();
        while (it != itFinal) {
            cout << it.elem();
            it.avanza();
        }
        cout << endl;
        cout << "AP9Sartego\n";
        l = m.multasPorTramos("AP9Sartego");
        it = l.principio();
        itFinal = l.final();
        while (it != itFinal) {
            cout << it.elem();
            it.avanza();
        }
        cout << endl;
        cout << "Zaragoza";
        l = m.multasPorTramos("AP9Sartego");
        it = l.principio();
        itFinal = l.final();
        while (it != itFinal) {
            cout << it.elem();
            it.avanza();
        }
        cout << endl;
        cout << "A7Torrox";
        l = m.multasPorTramos("A7Torrox");
        it = l.principio();
        itFinal = l.final();
        while (it != itFinal) {
            cout << it.elem();
            it.avanza();
        }
	}
	catch (ECamaraRepetida& e){ cout << "Camara repetida \n";}
	catch (ETramoRepetido& e) {cout << "Tramo repetido \n";}
	catch (ECamaraInexistente& e) {cout << "Camara inexistente \n";}
	catch (ETramoInexistente& e) {cout << "Tramo inexistente \n";}
    
	return 0;
}
