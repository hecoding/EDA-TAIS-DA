/**
 @file Hash.h
 
 Declaraci?n e implementaci?n de funciones de localizaci?n para
 tipos b?sicos y funci?n gen?rica que conf?a en la existencia
 del m?todo m?todo hash de las clases.
 
 Estructura de Datos y Algoritmos
 Facultad de Inform?tica
 Universidad Complutense de Madrid
 
 (c) Antonio S?nchez Ruiz-Granados, 2012
 */

#ifndef __HASH_H
#define __HASH_H

#include <string>

// ----------------------------------------------------
//
// Funciones hash para distintos tipos de datos b?sicos
//
// ----------------------------------------------------


inline unsigned int hash(unsigned int clave) {
	return clave;
}

inline unsigned int hash(int clave) {
	return (unsigned int) clave;
}

inline unsigned int hash(char clave) {
	return clave;
}

// Nota: Esta funci?n de hash para cadenas no es muy buena.
inline unsigned int hash(std::string clave) {
	
	// Suma los valores ASCII de todos sus caracters.
	unsigned int valor = 0;
	for (unsigned int i=0; i<clave.length(); ++i) {
		valor += clave[i];
	}
	return valor;
}


/**
 * Funci?n hash gen?rica para clases que implementen un
 * m?todo publico hash.
 */
template<class C>
unsigned int hash(const C &clave) {
	return clave.hash();
}


#endif // __HASH_H
