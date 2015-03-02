#ifndef ARBIN_H_
#define ARBIN_H_

#include <iostream>
#include <string>
#include <cassert>
#include <cstddef>

#include "../ejArboles4/Cola.h"
#include "../ejArboles4/Excepciones.h"
#include "../ejArboles4/Lista.h"
using namespace std;

class EArbolVacio : public ExcepcionTAD {
    public :
	EArbolVacio () {};
	EArbolVacio(const std :: string &msg) : ExcepcionTAD(msg) {}
};


template <class T>
class Arbin {
public:
	Arbin() : _ra(NULL){}
    
	Arbin(const Arbin &iz, const T &elem, const Arbin &dr) :
	_ra(new Nodo(copiaAux(iz._ra), elem, copiaAux(dr._ra))) {
	}
    
    // Constructor copia
	Arbin(const Arbin<T> &other) : _ra(NULL) {
        _ra = copiaAux(other._ra);
    }
    
    ~Arbin() {
        libera(_ra);
        _ra = NULL;
    }
    
    Arbin(Lista<T> lin, Lista<T> lpre){
    	_ra = construirRec(lin, lpre);
    }
    
	//Devuelve un árbol copia del árbol izquierdo (parcial).
	Arbin hijoIz() const {
	    if (esVacio()) throw EArbolVacio();
	    return Arbin(copiaAux(_ra->_iz));
	}
    
	//Devuelve un árbol copia del árbol derecho (parcial).
	Arbin hijoDr() const {
	    if (esVacio()) throw EArbolVacio();
	    return Arbin(copiaAux(_ra->_dr));
	}
    
	//Devuelve el elemento almacenado en la raiz
	const T &raiz() const {
	    if (esVacio())  throw EArbolVacio();
	    return _ra->_elem;
	}
    
	// Operación observadora que devuelve si el árbol
	// es vacío (no contiene elementos) o no.
	bool esVacio() const {
	    return _ra == NULL;
	}
    
    // Operador de asignacion
    Arbin &operator=(const Arbin &other ) {
        if (this != &other) {
            libera(_ra);
            _ra = copiaAux(other);
        }
        return *this;
    }
    
    
	//Operación observadora que indica si dos Arbin
	// son equivalentes.
	bool operator==(const Arbin &a) const {
	    return comparaAux(_ra, a._ra);
	}
        
        bool operator!=(const Arbin &a) const {
            return !operator==(a);
        }
    
	Lista<T> preorden() const {
	    Lista<T> ret;
	    preordenAcu(_ra, ret);
	    return ret;
	}
    
	Lista<T> inorden() const {
	    Lista<T> ret;
	    inordenAcu(_ra, ret);
	    return ret;
	}
    
	Lista<T> postorden() const {
	    Lista<T> ret;
	    postordenAcu(_ra, ret);
	    return ret;
	}
    
    
	Lista<T> niveles() const {
	    if (esVacio()) return Lista<T>();
	    Lista<T> ret;
	    Cola<Nodo*> porProcesar;
	    porProcesar.ponDetras(_ra);
	    while (!porProcesar.esVacia()) {
	        Nodo *visita = porProcesar.primero();
	        porProcesar.quitaPrim();
	        ret.ponDr(visita->_elem);
	        if (visita->_iz != NULL)
	            porProcesar.ponDetras(visita->_iz);
	        if (visita->_dr != NULL)
	            porProcesar.ponDetras(visita->_dr);
	    }
	    return ret;
	}
    
        bool esHoja() const {
		if (_ra == NULL) return false;

		return (_ra->_iz == NULL) && (_ra->_dr == NULL);
	}
   
protected:
    class Nodo {
    public:
        Nodo() : _iz(NULL), _dr(NULL) {}
        Nodo(const T &elem) :
        _elem(elem), _iz(NULL), _dr(NULL) {}
        Nodo(Nodo *iz, const T &elem, Nodo *dr) :
        _elem(elem), _iz(iz), _dr(dr) {}
        
        T _elem;
        Nodo *_iz;
        Nodo *_dr;
    };
    
private:
    //Puntero a la raíz
    Nodo *_ra;
    // Constructor privado. Construye un arbol a partir de un puntero a un nodo
 	Arbin(Nodo* ra) : _ra(ra){}
    
    static void libera(Nodo *ra) {
        if (ra != NULL) {
            libera(ra->_iz);
            libera(ra->_dr);
            delete ra;
        }
    }
    
    static Nodo *copiaAux(Nodo *ra) {
        if (ra == NULL)  return NULL;
        return new Nodo(copiaAux(ra->_iz), ra->_elem,
                        copiaAux(ra->_dr));
    }
    
    static bool comparaAux(Nodo *r1, Nodo *r2) {
        if (r1 == r2)
            return true;
        else if ((r1 == NULL) || (r2 == NULL))
            // En el if anterior nos aseguramos de
            // que r1 != r2. Si uno es NULL, el
            // otro entonces no lo será, luego
            // son distintos.
            return false;
        else {
            return (r1->_elem == r2->_elem) &&
            comparaAux(r1->_iz, r2->_iz) &&
            comparaAux(r1->_dr, r2->_dr);
        }
    }
    
    Nodo* construirRec(Lista<T> lin, Lista<T> lpre) {
        if (lpre.esVacia()) return NULL;
        T raiz = lpre.primero();
        int n = lin.buscaPos(raiz);
        lpre.resto();
        Lista<T> linIz = lin.coge(n-1);
        Lista<T> linDr = lin.quita(n);
        Lista<T> lpreIz = lpre.coge(n-1);
        Lista<T> lpreDr = lpre.quita(n-1);
        return new Nodo(construirRec(linIz,lpreIz),raiz,construirRec(linDr,lpreDr));
    }
    
 	static void preordenAcu(Nodo *ra, Lista<T> &acu) {
 	    if (ra == NULL) return;
        
 	    acu.ponDr(ra->_elem);
 	    preordenAcu(ra->_iz, acu);
 	    preordenAcu(ra->_dr, acu);
 	}
    
 	static void inordenAcu(Nodo *ra, Lista<T> &acu) {
 	    if (ra == NULL) return;
        
 	    inordenAcu(ra->_iz, acu);
 	    acu.ponDr(ra->_elem);
 	    inordenAcu(ra->_dr, acu);
 	}
    
    
 	static void postordenAcu(Nodo *ra, Lista<T> &acu) {
 	    if (ra == NULL)   return;
        
 	    postordenAcu(ra->_iz, acu);
 	    postordenAcu(ra->_dr, acu);
 	    acu.ponDr(ra->_elem);
 	}
    
};




#endif /* ARBIN_H_ */