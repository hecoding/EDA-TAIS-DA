#ifndef COLAMEDIANAS_H
#define COLAMEDIANAS_H

#include <iostream>
#include "ColaPrio.h"

template <class T, bool(*antes)(const T &, const T &), bool(*despues)(const T &, const T &)>
class ColaMedianas {
public:
	ColaMedianas() : _colamin(), _colamax() {}

	~ColaMedianas() {}

	void inserta(const int& x) {
		if (_colamin.numElem() == _colamax.numElem() && _colamin.numElem() == 0)
			_colamin.inserta(x);
		else if (x > mediana())
			_colamin.inserta(x);
		else
			_colamax.inserta(x);

		recolocar();
	}

	const int& mediana() const {
		if (_colamin.numElem() > _colamax.numElem())
			return _colamin.primero();
		else if (_colamin.numElem() < _colamax.numElem())
			return _colamax.primero();
		else { // igual altura
			return _colamin.primero(); // TODO calcular qué hacer en este caso
		}
	}

	void quitaMediana() {
		if (_colamin.numElem() > _colamax.numElem())
			_colamin.quitaPrim();
		else if (_colamin.numElem() < _colamax.numElem())
			_colamax.quitaPrim();
		else { // igual altura
			_colamin.quitaPrim(); // TODO calcular qué hacer en este caso
		}

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


	void recolocar() {
		int temp;

		while (_colamin.numElem() - _colamax.numElem() > 1) {

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

};

template <class T, bool(*antes)(const T &, const T &), bool(*despues)(const T &, const T &)>
inline ostream& operator<<(ostream& o,const ColaMedianas<T, antes, despues>& a){
    a.mostrar(o);
    return o;
}

#endif
