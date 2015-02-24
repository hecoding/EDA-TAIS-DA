
#ifndef AVL_H_
#define AVL_H_

using namespace std;

/* Excepcion provocada cuando se busca una clave que no esta. */
class EClaveErronea {
public:
	EClaveErronea() {};
	EClaveErronea(const string &msg) : _msg(msg) {}
	string msg() const { return _msg; }
protected:
	string _msg;
};

template <class Clave, class Valor>
class AVL {
protected:
    /**
    Clase nodo que almacena internamente la pareja (clave, valor),
    los punteros al hijo izquierdo y al hijo derecho, y la altura.
     */
    class Nodo {
    public:
        Clave clave;
        Valor valor;
        Nodo* iz;
        Nodo* dr;
        int altura;
        Nodo(const Clave& c, const Valor& v, Nodo* i=NULL, Nodo* d=NULL, int alt=1)
        : clave(c), valor(v), iz(i), dr(d), altura(alt) {}
    };

public:

    /** constructor */
    AVL() : raiz(NULL) {};

    /** destructor */
    ~AVL(){
        libera();
        raiz = NULL;
    };

    void inserta(const Clave &c, const Valor &v) {
        inserta(c, v, raiz);
    }

    bool esVacio() const {
        return raiz == NULL;
    }

    bool esta(const Clave& c) const {
        return busca(c, raiz) != NULL;
    }

    const Valor& consulta(const Clave &clave) {
        Nodo* p = busca(clave, raiz);
        if (p == NULL)
            throw EClaveErronea("La clave no se puede consultar");
        return p->valor;
    }

    void mostrar(ostream& o, int indent) const {
        mostrar(o,indent,raiz);
    }

    /** Constructor copia */
    AVL(const AVL<Clave, Valor>& other) : raiz(NULL) {
        copia(other);
    }

    /** Operador de asignacion */
    AVL<Clave, Valor>& operator=(const AVL<Clave, Valor> &other) {
        if (this != &other) {
            libera();
            copia(other);
        }
        return *this;
    }

protected:

    void libera(){
        libera(raiz);
    }

    void copia(const AVL<Clave, Valor>& a){
        copia(raiz,a.raiz);
    }

protected:

    /**
    Puntero a la raiz de la estructura jerarquica de nodos.
     */
    Nodo* raiz;

    static void libera(Nodo* a){
        if (a != NULL){
            libera(a->iz);
            libera(a->dr);
            delete a;
        }
    }

    static void copia(Nodo*& a,Nodo* b){
        if(b==NULL) a = NULL;
        else{
            Nodo* iz, *dr;
            copia(iz,b->iz);
            copia(dr,b->dr);
            a = new Nodo(b->clave,b->valor,iz,dr,max(altura(iz),altura(dr))+1);
        }
    }


    /*   static bool esta(const Clave& c, Nodo* a){
      if (a==NULL)
         return false;
      else if(a->clave < c)
         return esta(c, a->dr);
      else if(a->clave > c)
         return esta(c, a->iz);
      else
         return true;
   }
     */

    static Nodo* busca(const Clave& c, Nodo* a) {
        if (a == NULL)
            return NULL;
        else if (a->clave == c)
            return a;
        else if (c < a->clave)
            return busca(c, a->iz);
        else // c > a->clave
            return busca(c, a->dr);
    }

    static int altura(Nodo* a){
        if (a==NULL) return 0;
        else return a->altura;
    }

    static void inserta(const Clave& c, const Valor& v, Nodo*& a){
        if (a == NULL) {
            a = new Nodo(c,v);
        } else if (c == a->clave) {
            a->valor = v;
        } else if (c < a->clave) {
            inserta(c, v, a->iz);
            reequilibraDer(a);
        } else { // c > a->clave
            inserta(c, v, a->dr);
            reequilibraIzq(a);
        }
    }

    static void rotaDer(Nodo*& k2){
        Nodo* k1 = k2->iz;
        k2->iz = k1->dr;
        k1->dr = k2;
        k2->altura = max(altura(k2->iz),altura(k2->dr))+1;
        k1->altura = max(altura(k1->iz),altura(k1->dr))+1;
        k2 = k1;
    }

    static void rotaIzq(Nodo*& k1){
        Nodo* k2 = k1->dr;
        k1->dr = k2->iz;
        k2->iz = k1;
        k1->altura = max(altura(k1->iz),altura(k1->dr))+1;
        k2->altura = max(altura(k2->iz),altura(k2->dr))+1;
        k1=k2;
    }

    static void rotaIzqDer(Nodo*& k3){
        rotaIzq(k3->iz);
        rotaDer(k3);
    }

    static void rotaDerIzq(Nodo*& k1){
        rotaDer(k1->dr);
        rotaIzq(k1);
    }

    static void reequilibraIzq(Nodo*& a){
        if (altura(a->dr)-altura(a->iz) > 1) {
            if (altura(a->dr->iz) > altura(a->dr->dr))
                rotaDerIzq(a);
            else rotaIzq(a);
        }
        else a->altura = max(altura(a->iz),altura(a->dr))+1;
    }


    static void reequilibraDer(Nodo*& a){
        if (altura(a->iz)-altura(a->dr) > 1) {
            if (altura(a->iz->dr) > altura(a->iz->iz))
                rotaIzqDer(a);
            else rotaDer(a);
        }
        else a->altura = max(altura(a->iz),altura(a->dr))+1;
    }

    void mostrar(ostream& o,int indent, Nodo* r) const {
        if(r!=NULL){
            mostrar(o,indent+2,r->dr);
            for(int i=0;i<indent;i++) o << " ";
            o << "(" << r->clave << "," << r-> valor << ")" << endl;
            mostrar(o,indent+2,r->iz);
        }
    }

};


template <class Clave, class Valor>
ostream& operator<<(ostream& o,const AVL<Clave, Valor>& a){
    a.mostrar(o, 0);
    return o;
}




#endif /* AVL_H_ */
