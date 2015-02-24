#ifndef COLAMEDIANAS_H
#define COLAMEDIANAS_H

#include <iostream>
#include "../tiposdelprofesor/ColaPrio.h"

template <class T, bool(*antes)(const T &, const T &), bool(*despues)(const T &, const T &)> // pasar funciones como el profesor...
class ColaMedianas {

public:
	ColaMedianas() : _colamin(), _colamax() {}

	~ColaMedianas() {}

	void inserta(const int& x) {
		if (_colamin.esVacia() && _colamax.esVacia())
			_colamin.inserta(x); // da igual dónde se inserte al estar vacías

		else if (x > mediana())
			_colamin.inserta(x); // montículo de mínimos para los valores mayores que la mediana

		else _colamax.inserta(x); // montículo de máximos para los valores menores que la mediana

		recolocar();
	}

	const int& mediana() const {
		if (_colamin.numElem() > _colamax.numElem())
			return _colamin.primero();

		else if (_colamin.numElem() < _colamax.numElem())
			return _colamax.primero();

		else // igual altura, la mediana está en el montículo de máximos
			return _colamax.primero();

	}

	void quitaMediana() {
		if (_colamin.numElem() > _colamax.numElem())
			_colamin.quitaPrim();

		else if (_colamin.numElem() < _colamax.numElem())
			_colamax.quitaPrim();

		else // igual altura, la mediana está en el montículo de máximos
			_colamax.quitaPrim();

		recolocar();
	}

	void mostrar(ostream& o) const {
		o << "min: ";
		_colamin.mostrar(o);
		o << std::endl;
		o << "max: ";
		_colamax.mostrar(o);
	}

private:

	ColaPrio<int, antes> _colamin;
	ColaPrio<int, despues> _colamax;

	/** función que balancea los dos montículos */
	void recolocar() {
		int temp { };

		while (abs(_colamin.numElem() - _colamax.numElem()) > 1) {

			if (_colamin.numElem() - _colamax.numElem() > 1) {
				temp = _colamin.primero();
				_colamin.quitaPrim();
				_colamax.inserta(temp);

			} else if (_colamin.numElem() - _colamax.numElem() < 1) {
				temp = _colamax.primero();
				_colamax.quitaPrim();
				_colamin.inserta(temp);
			}

		}
	}

	unsigned int abs (int x) {
		if (x > 0) return x;
		else return -x;
	}

};

template <class T, bool(*antes)(const T &, const T &), bool(*despues)(const T &, const T &)>
inline ostream& operator<<(ostream& o,const ColaMedianas<T, antes, despues>& a){
    a.mostrar(o);
    return o;
}

#endif
