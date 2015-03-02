#ifndef __ARBUS_H
#define __ARBUS_H

#include "../ejArboles4/Excepciones.h"
#include "../ejArboles4/Lista.h" // Tipo devuelto por los recorridos
#include "../ejArboles4/Pila.h" // Usado internamente por los iteradores

/**
 ImplementaciÛn din·mica del TAD Arbus utilizando
 nodos con un puntero al hijo izquierdo y otro al
 hijo derecho.
 
 Las operaciones son:
 
 - ArbusVacio: operaciÛn generadora que construye
 un ·rbol de b˙squeda vacÌo.
 
 - Inserta(clave, valor): generadora que aÒade una
 nueva pareja (clave, valor) al ·rbol. Si la
 clave ya estaba se sustituye el valor.
 
 - borra(clave): operaciÛn modificadora. Elimina la
 clave del ·rbol de b˙squeda.  Si la clave no est·,
 la operaciÛn no tiene efecto.
 
 - consulta(clave): operaciÛn observadora que devuelve
 el valor asociado a una clave. Es un error preguntar
 por una clave que no existe.
 
 - esta(clave): operaciÛn observadora. Sirve para
 averiguar si se ha introducido una clave en el
 ·rbol.
 
 - esVacio(): operacion observadora que indica si
 el ·rbol de b˙squeda tiene alguna clave introducida.
 
 @author Marco Antonio GÛmez MartÌn
 */
class EClaveErronea : public ExcepcionTAD {
    public :
	EClaveErronea () {};
	EClaveErronea(const std :: string &msg) : ExcepcionTAD(msg) {}
};


template <class Clave, class Valor>
class Arbus {
private:
	/**
	 Clase nodo que almacena internamente la pareja (clave, valor)
	 y los punteros al hijo izquierdo y al hijo derecho.
	 */
	class Nodo {
	public:
		Nodo() : _iz(NULL), _dr(NULL) {}
		Nodo(const Clave &clave, const Valor &valor)
        : _clave(clave), _valor(valor), _iz(NULL), _dr(NULL) {}
		Nodo(Nodo *iz, const Clave &clave, const Valor &valor, Nodo *dr)
        : _clave(clave), _valor(valor), _iz(iz), _dr(dr) {}
        
		Clave _clave;
		Valor _valor;
		Nodo *_iz;
		Nodo *_dr;
	};
    
public:
    
	/** Constructor; operacion ArbolVacio */
	Arbus() : _ra(NULL) {
	}
    
	/** Destructor; elimina la estructura jer·rquica de nodos. */
	~Arbus() {
		libera();
		_ra = NULL;
	}
    
	/**
	 OperaciÛn generadora que aÒade una nueva clave/valor
	 a un ·rbol de b˙squeda.
	 @param clave Clave nueva.
	 @param valor Valor asociado a esa clave. Si la clave
	 ya se habÌa insertado previamente, sustituimos el valor
	 viejo por el nuevo.
	 */
	void inserta(const Clave &clave, const Valor &valor) {
		_ra = insertaAux(clave, valor, _ra);
	}
    
	/**
	 OperaciÛn modificadora que elimina una clave del ·rbol.
	 Si la clave no existÌa la operaciÛn no tiene efecto.
     
     borra(elem, ArbusVacio) = ArbusVacio
     borra(e, inserta(c, v, arbol)) =
     inserta(c, v, borra(e, arbol)) si c != e
     borra(e, inserta(c, v, arbol)) = borra(e, arbol) si c == e
     
	 @param clave Clave a eliminar.
	 */
	void borra(const Clave &clave) {
		_ra = borraAux(_ra, clave);
	}
    
	/**
	 OperaciÛn observadora que devuelve el valor asociado
	 a una clave dada.
     
	 consulta(e, inserta(c, v, arbol)) = v si e == c
	 consulta(e, inserta(c, v, arbol)) = consulta(e, arbol) si e != c
	 error consulta(ArbusVacio)
     
	 @param clave Clave por la que se pregunta.
	 */
	const Valor &consulta(const Clave &clave) {
		Nodo *p = buscaAux(_ra, clave);
		if (p == NULL)
			throw EClaveErronea();
        
		return p->_valor;
	}
    
	/**
	 OperaciÛn observadora que permite averiguar si una clave
	 determinada est· o no en el ·rbol de b˙squeda.
     
	 esta(e, ArbusVacio) = false
	 esta(e, inserta(c, v, arbol)) = true si e == c
	 esta(e, inserta(c, v, arbol)) = esta(e, arbol) si e != c
     
	 @param clave Clave por la que se pregunta.
	 */
	bool esta(const Clave &clave) {
		return buscaAux(_ra, clave) != NULL;
	}
    
	/**
	 OperaciÛn observadora que devuelve si el ·rbol
	 es vacÌo (no contiene elementos) o no.
     
	 esVacio(ArbusVacio) = true
	 esVacio(inserta(c, v, arbol)) = false
	 */
	bool esVacio() const {
		return _ra == NULL;
	}
    
	Lista<Clave> inorden() const {
	    Lista<Clave> ret;
	    inordenAcu(_ra, ret);
	    return ret;
	}
    
    
	// //
	// OPERACIONES RELACIONADAS CON LOS ITERADORES
	// //
    
	/**
	 Clase interna que implementa un iterador sobre
	 la lista que permite recorrer la lista e incluso
	 alterar el valor de sus elementos.
	 */
	class Iterador {
	public:
		void avanza() {
			if (_act == NULL) throw EAccesoInvalido();
            
			// Si hay hijo derecho, saltamos al primero
			// en inorden del hijo derecho
			if (_act->_dr)
				_act = primeroInOrden(_act->_dr);
			else {
				// Si no, vamos al primer ascendiente
				// no visitado. Para eso consultamos
				// la pila; si ya est· vacÌa, no quedan
				// ascendientes por visitar
				if (_ascendientes.esVacia())
					_act = NULL;
				else {
					_act = _ascendientes.cima();
					_ascendientes.desapila();
				}
			}
		}
        
		const Clave &clave() const {
			if (_act == NULL) throw EAccesoInvalido();
			return _act->_clave;
		}
        
		const Valor &valor() const {
			if (_act == NULL) throw EAccesoInvalido();
			return _act->_valor;
		}
        
		bool operator==(const Iterador &other) const {
			return _act == other._act;
		}
        
		bool operator!=(const Iterador &other) const {
			return !(this->operator==(other));
		}
        
	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class Arbus;
        
		Iterador() : _act(NULL) {}
		Iterador(Nodo *act) {
			_act = primeroInOrden(act);
		}
        
		/**
		 Busca el primer elemento en inorden de
		 la estructura jer·rquica de nodos pasada
		 como par·metro; va apilando sus ascendientes
		 para poder "ir hacia atr·s" cuando sea necesario.
		 @param p Puntero a la raÌz de la subestructura.
		 */
		Nodo *primeroInOrden(Nodo *p) {
			if (p == NULL)
				return NULL;
            
			while (p->_iz != NULL) {
				_ascendientes.apila(p);
				p = p->_iz;
			}
			return p;
		}
        
		// Puntero al nodo actual del recorrido
		// NULL si hemos llegado al final.
		Nodo *_act;
        
		// Ascendientes del nodo actual
		// a˙n por visitar
		PilaLE<Nodo*> _ascendientes;
	};
    
	/**
	 Devuelve el iterador al principio de la lista.
	 @return iterador al principio de la lista;
	 coincidir· con final() si la lista est· vacÌa.
	 */
	Iterador principio() const {
		return Iterador(_ra);
	}
    
	/**
	 @return Devuelve un iterador al final del recorrido
	 (fuera de Èste).
	 */
	Iterador final() const {
		return Iterador(NULL);
	}
    
    
	// //
	// M…TODOS DE "FONTANERÕA" DE C++ QUE HACEN VERS¡TIL
	// A LA CLASE
	// //
    
	/** Constructor copia */
	Arbus(const Arbus<Clave, Valor> &other) : _ra(NULL) {
		copia(other);
	}
    
	/** Operador de asignaciÛn */
	Arbus<Clave, Valor> &operator=(const Arbus<Clave, Valor> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}
    
	/** Operador de igualdad */
	bool operator==(const Arbus<Clave, Valor> &other) {
		Iterador it = principio();
		Iterador itFinal = final();
		Iterador itOther = other.principio();
		Iterador itOtherFinal = other.final();
        
		while (it != itFinal && itOther != itOtherFinal && it.clave() == itOther.clave() && it.valor() == itOther.valor()) {
			it.avanza();
			itOther.avanza();
		}
		return it == itFinal && itOther == itOtherFinal;
	}
    
protected:
    
	/**
	 Constructor protegido que crea un ·rbol
	 a partir de una estructura jer·rquica de nodos
	 previamente creada.
	 Se utiliza en hijoIz e hijoDr.
	 */
	Arbus(Nodo *raiz) : _ra(raiz) {
	}
    
	void libera() {
		libera(_ra);
	}
    
	void copia(const Arbus &other) {
		_ra = copiaAux(other._ra);
	}
    
private:
    
	/**
	 Elimina todos los nodos de una estructura arbÛrea
	 que comienza con el puntero ra.
	 Se admite que el nodo sea NULL (no habr· nada que
	 liberar).
	 */
	static void libera(Nodo *ra) {
		if (ra != NULL) {
			libera(ra->_iz);
			libera(ra->_dr);
			delete ra;
		}
	}
    
	/**
	 Copia la estructura jer·rquica de nodos pasada
	 como par·metro (puntero a su raiz) y devuelve un
	 puntero a una nueva estructura jer·rquica, copia
	 de anterior (y que, por tanto, habr· que liberar).
	 */
	static Nodo *copiaAux(Nodo *ra) {
		if (ra == NULL)
			return NULL;
        
		return new Nodo(copiaAux(ra->_iz),
						ra->_clave, ra->_valor,
						copiaAux(ra->_dr));
	}
    
	/**
	 Inserta una pareja (clave, valor) en la estructura
	 jer·rquica que comienza en el puntero pasado como par·metro.
	 Ese puntero se admite que sea NULL, por lo que se crear·
	 un nuevo nodo que pasar· a ser la nueva raÌz de esa
	 estructura jer·rquica. El mÈtodo devuelve un puntero a la
	 raÌz de la estructura modificada. En condiciones normales
	 coincidir· con el par·metro recibido; sÛlo cambiar· si
	 la estructura era vacÌa.
	 @param clave Clave a insertar. Si ya aparecÌa en la
	 estructura de nodos, se sobreescribe el valor.
	 @param valor Valor a insertar.
	 @param p Puntero al nodo raÌz donde insertar la pareja.
	 @return Nueva raÌz (o p si no cambia).
	 */
	static Nodo *insertaAux(const Clave &clave, const Valor &valor, Nodo *p) {
        
		if (p == NULL) {
			return new Nodo(clave, valor);
		} else if (p->_clave == clave) {
			p->_valor = valor;
			return p;
		} else if (clave < p->_clave) {
			p->_iz = insertaAux(clave, valor, p->_iz);
			return p;
		} else { // (clave > p->_clave)
			p->_dr = insertaAux(clave, valor, p->_dr);
			return p;
		}
	}
    
	/**
	 Busca una clave en la estructura jer·rquica de
	 nodos cuya raÌz se pasa como par·metro, y devuelve
	 el nodo en la que se encuentra (o NULL si no est·).
	 @param p Puntero a la raÌz de la estructura de nodos
	 @param clave Clave a buscar
	 */
	static Nodo *buscaAux(Nodo *p, const Clave &clave) {
		if (p == NULL)
			return NULL;
        
		if (p->_clave == clave)
			return p;
        
		if (clave < p->_clave)
			return buscaAux(p->_iz, clave);
		else
			return buscaAux(p->_dr, clave);
	}
    
	/**
	 Elimina (si existe) la clave/valor de la estructura jer·rquica
	 de nodos apuntada por p. Si la clave aparecÌa en la propia raÌz,
	 Èsta cambiar·, por lo que se devuelve la nueva raÌz. Si no cambia
	 se devuelve p.
     
	 @param p RaÌz de la estructura jer·rquica donde borrar la clave.
	 @param clave Clave a borrar.
	 @return Nueva raÌz de la estructura, tras el borrado. Si la raÌz
	 no cambia, se devuelve el propio p.
     */
	static Nodo *borraAux(Nodo *p, const Clave &clave) {
        
		if (p == NULL)
			return NULL;
        
		if (clave == p->_clave) {
			return borraRaiz(p);
		} else if (clave < p->_clave) {
			p->_iz = borraAux(p->_iz, clave);
			return p;
		} else { // clave > p->_clave
			p->_dr = borraAux(p->_dr, clave);
			return p;
		}
	}
    
	/**
	 Borra la raÌz de la estructura jer·rquica de nodos
	 y devuelve el puntero a la nueva raÌz que garantiza
	 que la estructura sigue siendo v·lida para un ·rbol de
	 b˙squeda (claves ordenadas).
	 */
	static Nodo *borraRaiz(Nodo *p) {
        
		Nodo *aux;
        
		// Si no hay hijo izquierdo, la raÌz pasa a ser
		// el hijo derecho
		if (p->_iz == NULL) {
			aux = p->_dr;
			delete p;
			return aux;
		} else
            // Si no hay hijo derecho, la raÌz pasa a ser
            // el hijo izquierdo
            if (p->_dr == NULL) {
                aux = p->_iz;
                delete p;
                return aux;
            } else {
                // Convertimos el elemento m·s pequeÒo del hijo derecho
                // en la raÌz.
                return mueveMinYBorra(p);
            }
	}
    
	/**
	 MÈtodo auxiliar para el borrado; recibe un puntero a la
	 raÌz a borrar. Busca el elemento m·s pequeÒo del hijo derecho
	 que se convertir· en la raÌz (que devolver·), borra la antigua
	 raÌz (p) y "cose" todos los punteros, de forma que ahora:
     
     - El mÌnimo pasa a ser la raÌz, cuyo hijo izquierdo y
     derecho eran los hijos izquierdo y derecho de la raÌz
     antigua.
     - El hijo izquierdo del padre del elemento m·s pequeÒo
     pasa a ser el antiguo hijo derecho de ese mÌnimo.
	 */
	static Nodo *mueveMinYBorra(Nodo *p) {
        
		// Vamos bajando hasta que encontramos el elemento
		// m·s pequeÒo (aquel que no tiene hijo izquierdo).
		// Vamos guardando tambiÈn el padre (que ser· null
		// si el hijo derecho es directamente el elemento
		// m·s pequeÒo).
		Nodo *padre = NULL;
		Nodo *aux = p->_dr;
		while (aux->_iz != NULL) {
			padre = aux;
			aux = aux->_iz;
		}
        
		// aux apunta al elemento m·s pequeÒo.
		// padre apunta a su padre (si el nodo es hijo izquierdo)
        
		// Dos casos dependiendo de si el padre del nodo con
		// el mÌnimo es o no la raÌz a eliminar
		// (=> padre != NULL)
		if (padre != NULL) {
			padre->_iz = aux->_dr;
			aux->_iz = p->_iz;
			aux->_dr = p->_dr;
		} else {
			aux->_iz = p->_iz;
		}
        
		delete p;
		return aux;
	}
    
 	static void inordenAcu(Nodo *ra, Lista<Clave> &acu) {
 	    if (ra == NULL) return;
        
 	    inordenAcu(ra->_iz, acu);
 	    acu.ponDr(ra->_clave);
 	    inordenAcu(ra->_dr, acu);
 	}
    
    
	/**
	 Puntero a la raÌz de la estructura jer·rquica
	 de nodos.
	 */
	Nodo *_ra;
};

#endif // __Arbus_H