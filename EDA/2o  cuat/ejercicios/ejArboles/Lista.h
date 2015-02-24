#ifndef LISTA_H_
#define LISTA_H_

#include <iostream>
#include <string>
#include <cassert>
#include <cstddef>
using namespace std;
#include "Excepciones.h"



//Excepciones generadas por algunos metodos. // class EListaVacia {};
class EAccesoInvalido : public ExcepcionTAD {
	public :
	EAccesoInvalido () {};
	EAccesoInvalido(const std :: string &msg) : ExcepcionTAD(msg) {}
};
class EListaVacia : public ExcepcionTAD {
	public :
    EListaVacia () {};
    EListaVacia(const std :: string &msg) : ExcepcionTAD(msg) {}
};


template <class T>
class Lista {
private:
    class Nodo {
    public:
        Nodo() : _ant(NULL), _sig(NULL) {}
        Nodo(const T &elem) : _elem(elem), _sig(NULL), _ant(NULL) {}
        Nodo(Nodo* ant, const T &elem, Nodo *sig) : _elem(elem), _sig(sig), _ant(ant) {}
        T _elem;
        Nodo *_sig;
        Nodo *_ant;
    };
    Nodo *_prim, *_ult;
    unsigned int _numElems;
    
    void libera(Nodo* prim) {
        while (prim != NULL) {
            Nodo *aux = prim;
            prim = prim->_sig;
            delete aux;
        }
    }
    void copia(const Lista &other) {
        if (other.esVacia()) { _prim = NULL; _ult = NULL;}
        else {
            Nodo* act = other._prim ;
            Nodo* ant;
            _prim = new Nodo(act->_elem);
            ant = _prim;
            while (act->_sig != NULL) {
                act = act->_sig ;
                ant->_sig = new Nodo(ant,act->_elem,NULL);
                ant = ant->_sig ;
            }
            _ult = ant;
            _numElems = other._numElems;
        }
    }
    
public:
    Lista() : _prim(NULL), _ult(NULL), _numElems(0) {}
    // Constructor copia
    Lista(const Lista<T> &other) : _prim(NULL), _ult(NULL) {
        copia(other);
    }
    
    ~Lista(){ // destructor. elimina la lista
        libera(_prim);
        _prim = NULL;  _ult = NULL;
    }
    // Anade un nuevo elemento en la cabeza de la lista.
    // @param elem Elemento que se anade
    void Cons(const T &elem) {
        _numElems++;
        Nodo* nuevo = new Nodo(NULL,elem,_prim);
        if (_prim != NULL) _prim->_ant = nuevo;
        _prim = nuevo;
        if (_ult == NULL) _ult = _prim;
    }
    // anade un elemento al final de la lista.
    void ponDr(const T &elem) {
        _numElems++;
        Nodo * nuevo = new Nodo(_ult,elem,NULL);
        if (_ult != NULL) _ult->_sig = nuevo;
        _ult = nuevo;
        if (_prim == NULL) _prim = _ult;
    }
    
    // Devuelve el valor almacenado en la cabecera
    const T &primero() const {
    	if (esVacia()) throw EListaVacia();
    	return _prim->_elem;
    }
    // Devuelve el valor almacenado en la  ultima posicion
    const T &ultimo() const {
    	if (esVacia()) throw EListaVacia();
    	return _ult->_elem;
    }
    //Elimina el primer elemento de la lista.
    void resto() {
    	if (esVacia()) throw EListaVacia();
    	Nodo *aBorrar = _prim;
    	_prim = _prim->_sig;
    	if (_prim == NULL) _ult = NULL;
    	else _prim->_ant = NULL;
    	--_numElems;
    	delete aBorrar;
    }
    // Elimina el  ultimo elemento de la lista.
    void inicio() {
        if (esVacia()) throw EListaVacia();
        Nodo *aBorrar = _ult;
        _ult = _ult->_ant;
        if (_ult == NULL) _prim = NULL;
        else _ult->_sig = NULL;
        --_numElems;
        delete aBorrar;
    }
    
    // devuelve si la lista es vacia
    bool esVacia() const {
    	return _prim == NULL;
    }
    // Devuelve el numero de elementos de la lista.
    unsigned int numElems() const {
    	return _numElems;
    }
    // Devuelve el elemento i-esimo de la lista
    const T &elem(unsigned int idx) const {
        if (idx >= _numElems) throw EAccesoInvalido();
        Nodo *aux = _prim;
        for (int i = 0; i < idx; ++i)
            aux = aux->_sig; return aux->_elem;
    }
    
    void concatena (const Lista & other) {
    	Nodo* act = other._prim;
    	while (act != NULL) {
    		ponDr(act->_elem);
    		act = act->_sig;
    	}
    	_numElems +=other._numElems;
    }
    
    // Operador de asignacion
    Lista &operator=(const Lista &other ) {
        if (this != &other) {
            libera(_prim);
            copia(other);
        }
        return *this;
    }
    
    // Operador de comparacion .
    bool operator==(const Lista &rhs ) const {
        Nodo* prim1 = _prim;
        Nodo* prim2 = rhs._prim ;
        while ((prim1 != NULL) && (prim2 != NULL) &&
               prim1->_elem == prim2->_elem ) {
        	prim1 = prim1->_sig;
        	prim2 = prim2->_sig;
        }
        return (prim1 == NULL) && (prim2 == NULL);
    }
    
    friend ostream &operator<< (std::ostream &out, Lista &l){
    	Iterador it = l.principio();
    	Iterador itFinal = l.final();
    	while (it != itFinal) {
    		out << it.elem() << " " ;
    		it.avanza();
    	}
    	out << "\n";
        return out;
    }
    
    class Iterador {
    public:
        void avanza() {
            if (_act == NULL) throw EAccesoInvalido();
            _act = _act->_sig;
        }
        const T &elem() const {
            if (_act == NULL) throw EAccesoInvalido();
            return _act->_elem;
        }
        bool operator==(const Iterador &other) const {
            return _act == other._act;
        }
        bool operator!=(const Iterador &other) const {
            return !(this->operator==(other));
        }
   	protected:
        // Para que pueda construir objetos del tipo iterador
        friend class Lista;
        Iterador() : _act(NULL) {}
        Iterador(Nodo *act) : _act(act) {}
        // Puntero al nodo actual del recorrido
        Nodo *_act;
    };
    
    Iterador principio() const {
    	return Iterador(_prim);
    }
    Iterador final() const {
    	return Iterador(NULL);
    }
    
    class IteradorMutable {
    public:
        void avanza() {
            if (_act == NULL) throw EAccesoInvalido();
            _act = _act->_sig;
        }
        const T &elem() const {
            if (_act == NULL) throw EAccesoInvalido();
            return _act->_elem;
        }
        bool operator==(const IteradorMutable &other) const {
            return _act == other._act;
        }
        bool operator!=(const IteradorMutable &other) const {
            return !(this->operator==(other));
        }
        void pon (const T & elem){
            if (_act == NULL) throw EAccesoInvalido();
            _act->_elem = elem;
        }
        void modifica (T (*f)(T)){
            if (_act == NULL) throw EAccesoInvalido();
            _act->_elem = f(_act->_elem);
        }
    protected:
        // Para que pueda construir objetos del tipo iterador
        friend class Lista;
        IteradorMutable() : _act(NULL) {}
        IteradorMutable(Nodo *act) : _act(act) {}
        // Puntero al nodo actual del recorrido
        Nodo *_act;
    };
    
    IteradorMutable principioMut() {
    	return IteradorMutable(_prim);
    }
    IteradorMutable finalMut() {
    	return IteradorMutable(NULL);
    }
    
    class IteradorInverso {
    public:
        void avanza() {
            if (_act == NULL) throw EAccesoInvalido();
            _act = _act->_ant;
        }
        const T &elem() const {
            if (_act == NULL) throw EAccesoInvalido();
            return _act->_elem;
        }
        bool operator==(const IteradorInverso &other) const {
            return _act == other._act;
        }
        bool operator!=(const IteradorInverso &other) const {
            return !(this->operator==(other));
        }
   	protected:
        // Para que pueda construir objetos del tipo iterador
        friend class Lista;
        IteradorInverso() : _act(NULL) {}
        IteradorInverso(Nodo *act) : _act(act) {}
        // Puntero al nodo actual del recorrido
        Nodo *_act;
    };
    
    IteradorInverso principioInverso() const {
    	return IteradorInverso(_ult);
    }
    IteradorInverso finalInverso() const {
    	return IteradorInverso(NULL);
    }
    
    Lista<T> coge (int n) {
    	Lista<T> result;
    	Nodo* aux = _prim;
    	int i = 0;
    	while (i < n && aux != NULL) {
    		result.ponDr(aux->_elem);
    		aux = aux->_sig;
    		i++;
    	}
    	return result;
    }
    
    Lista<T> quita (int n) {
    	Lista<T> result;
    	Nodo* aux = _prim;
    	int i = 0;
    	while (aux != NULL && i < n) {
    		aux = aux->_sig;
    		i++;
    	}
    	while (aux != NULL) {
    		result.ponDr(aux->_elem);
    		aux = aux->_sig;
    	}
    	return result;
    }
    
    int buscaPos(const T & elem) {
    	Nodo* aux = _prim;
    	int i = 1;
    	while (aux != NULL && aux->_elem != elem) {
    		i++;
    		aux = aux->_sig;
    	}
    	return i;
    }
    
    
};

//template <class T>
// ostream &operator<< (std::ostream &out,const Lista<T> &l){
//	Lista<T>::Iterador it = l.principio();
//	Lista<T>::Iterador itFinal = l.final();
//	while (it != itFinal) {
//		out << it.elem() << " " ;
//		it.avanza();
//	}
//	out << "\n";
//    return out;
//}

#endif /* LISTA_H_ */