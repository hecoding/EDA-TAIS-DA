
#ifndef COLA_H_
#define COLA_H_

#include <iostream>
#include <string>
#include <cassert>
#include <cstddef>

#include "../ejArboles4/Excepciones.h"
using namespace std;

/** Excepción generada por algunos métodos. */
class EColaVacia : public ExcepcionTAD {
    public :
	EColaVacia () {};
	EColaVacia(const std :: string &msg) : ExcepcionTAD(msg) {}
};

template <class T>
class Cola {
    
public:
    /** Constructor; operacion ColaVacia */
    Cola() : _prim(NULL), _ult(NULL) {}
    
    // Constructor copia
    Cola(const Cola<T> &other) : _prim(NULL), _ult(NULL) {
        copia(other);
    }
    
    /** Destructor; elimina la lista enlazada. */
    ~Cola() {
        libera(_prim);
        _prim = _ult = NULL;
    }
    
    // Añade un elemento en la parte trasera de la cola.
    // @param elem Elemento a añadir.
    void ponDetras(const T &e) {
        Nodo *nuevo = new Nodo(e);
        if (_prim == NULL)  {_prim = nuevo; _ult = nuevo;}
        else {
            _ult->_sig = nuevo;
            _ult = nuevo;
        }
    }
    
    // Devuelve el primer elemento de la cola. Operación
    // observadora parcial, falla si la cola está vacía.
    const T &primero() const {
        if (esVacia())  throw EColaVacia();
        return _prim->_elem;
    }
    
    // Elimina el primer elemento de la cola.
    // Operación modificadora parcial, que falla si
    // la cola está vacía.
    void quitaPrim() {
        if (esVacia()) throw EColaVacia();
        Nodo *aBorrar = _prim;
        _prim = _prim->_sig;
        delete aBorrar;
        if (_prim == NULL) _ult = NULL;
    }
    
    // Devuelve true si la cola no tiene ningún elemento.
    bool esVacia() const {
        return _prim == NULL;
    }
    
    // Operador de asignacion
    Cola &operator=(const Cola &other ) {
        if (this != &other) {
            libera(_prim);
            copia(other);
        }
        return *this;
    }
    
    // Operador de comparacion .
    bool operator==(const Cola &rhs ) const {
        Nodo* prim1 = _prim;
        Nodo* prim2 = rhs._prim ;
        while ((prim1 != NULL) && (prim2 != NULL) &&
               prim1->_elem == prim2->_elem ) {
            prim1 = prim1->_sig;
            prim2 = prim2->_sig;
        }
        return (prim1 == NULL) && (prim2 == NULL);
    }
    
    friend ostream &operator<< (std::ostream &out, const Cola<T> &p) {
    	Cola<T> caux = p;
        while (!caux.esVacia() ) {
            out << caux.primero() << " ";
            caux.quitaPrim();
        }
        return out;
    }
    
private:
    class Nodo {
    public:
        Nodo() : _sig(NULL) {}
        Nodo(const T &elem) : _elem(elem), _sig(NULL) {}
        Nodo(const T &elem, Nodo *sig) : _elem(elem), _sig(sig) {}
        T _elem;
        Nodo *_sig;
    };
    // Puntero al primer y último elemento
    Nodo *_prim, *_ult;
    
    void libera(Nodo* prim) {
        while (prim != NULL) {
            Nodo *aux = prim;
            prim = prim->_sig;
            delete aux;
        }
    }
    
    void copia(const Cola &other) {
        if (other.esVacia()) { _prim = NULL; _ult = NULL;}
        else {
            Nodo* act = other._prim ;
            Nodo* ant;
            _prim = new Nodo(act->_elem);
            ant = _prim;
            while (act->_sig != NULL) {
                act = act->_sig ;
                ant->_sig = new Nodo(act->_elem );
                ant = ant->_sig ;
            }
            _ult = ant;
        }
    }
    
};

//template <class T>
//ostream &operator<< (std::ostream &out, const Cola<T> &p){
//	Cola<T> caux = p;
//    while (!caux.esVacia() ) {
//        out << caux.primero() << " ";
//        caux.quitaPrim();
//    }
//    return out;
//}

#endif /* COLA_H_ */