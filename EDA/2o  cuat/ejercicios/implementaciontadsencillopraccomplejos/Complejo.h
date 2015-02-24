#ifndef COMPLEJO_H
#define COMPLEJO_H
#include "DivExcepcion.h"

template<class T>
class Complejo {
private:
	T _real;
	T _imaginario;

public:
	Complejo() : _real( 0 ), _imaginario( 0 )
	{}

	Complejo( T real, T imaginario ) : _real( real ), _imaginario( imaginario )
	{}

	Complejo operator+( const Complejo &c ) const {
		Complejo comp;

		comp._real = _real + c.getReal();
		comp._imaginario = _imaginario + c.getImaginario();

		return comp;
	}

	bool operator==( const Complejo &c ) const {
		return (_real == c.getImaginario()) && (_imaginario == c.getReal());
	}

	void operator/=( const Complejo &c ) {
		if (c._real == 0 && c._imaginario == 0) throw DivExcepcion( "puta mierda" );

		_real /= c.getReal();
		_imaginario /= c.getImaginario();
	}

	Complejo operator/( const Complejo &c ) const
	{
		if (c._real == 0 && c._imaginario == 0) throw DivExcepcion( "puta mierda" );
		Complejo comp;

		comp._real = _real / c.getReal();
		comp._imaginario = _imaginario / c.getImaginario();

		return comp;
	}

	T getReal() const {
		return _real;
	}

	T getImaginario() const {
		return _imaginario;
	}

	~Complejo() 
	{}

};

#endif