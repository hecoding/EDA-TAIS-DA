/*
 * Grafo.h
 *
 *  Created on: 10/10/2012
 *      Author: Alberto Verdejo
 */

#ifndef GRAFO_H_
#define GRAFO_H_

#include <fstream>
#include <list>
#include <queue>
using namespace std;

class ExcepcionTAD {
public:
	ExcepcionTAD() {}
	ExcepcionTAD(const std::string &msg) : _msg(msg) {}
	const std::string msg() const { return _msg; }
protected:
	std::string _msg;
};

class VerticeInexistente : public ExcepcionTAD {
public:
	VerticeInexistente() {};
	VerticeInexistente(const std::string &msg) : ExcepcionTAD(msg) {}
};

class IllegalArgumentException : public ExcepcionTAD {
public:
	IllegalArgumentException() {};
	IllegalArgumentException(const std::string &msg) : ExcepcionTAD(msg) {}
};


typedef unsigned int uint;
typedef list<uint> Adys;
typedef list<uint> Path;

class Grafo {

private:
	uint _V;      // numero de vertices
	uint _E;      // numero de aristas
	Adys* _adj;   // vector de listas de adyacencia

public:

	/**
	 * Crea un grafo aleatorio con V vértices y E aristas.
	 */
	Grafo(uint v, uint e=0) : _V(v), _E(0), _adj(new Adys[_V]) {
		for (uint i = 0; i < e; i++) {
			uint v = rand() % _V; uint w = v;
			while(w == v) w = rand() % _V;
			ponArista(v, w);
		}
	}

	/**
	 * Crea un grafo a partir de un fichero de entrada.
	 */
	Grafo(string file) {
		ifstream ent(file);
		ent >> _V;
		_E = 0;
		_adj = new Adys[_V];
		uint e;
		ent >> e;
		uint v, w;
		for (uint i = 0; i < e; i++) {
			ent >> v;
			ent >> w;
			ponArista(v, w);
		}
		ent.close();
	}

	~Grafo(){
		delete[] _adj;
		_adj = NULL;
	}

	/**
	 * Constructor de copia.
	 */
	Grafo(const Grafo& G)  : _V(G.V()), _E(G.E()), _adj(new Adys[_V]) {
		copia(G);
	}

	/**
	 * Devuelve el número de vértices del grafo.
	 */
	uint V() const { return _V; }

	/**
	 * Devuelve el número de aristas del grafo.
	 */
	uint E() const { return _E; }

	/**
	 * Añade la arista v-w al grafo.
	 * @throws VerticeInexistente si algún vértice no existe
	 */
	void ponArista(uint v, uint w) {
		if (v >= _V || w >= _V) throw VerticeInexistente();
		_E++;
		_adj[v].push_back(w);
		_adj[w].push_back(v);
	}

	/**
	 * Devuelve la lista de adyacencia de v.
	 * @throws VerticeInexistente si v no existe
	 */
	const Adys& adj(uint v) const {
		if (v >= _V) throw new VerticeInexistente();
		return _adj[v];
	}


	/**
	 * Muestra el grafo en el stream de salida o
	 */
	void mostrar(ostream& o) const {
		o << _V << " vertices, " << _E << " aristas" << endl;
		for (uint v = 0; v < _V; v++) {
			o << v << ": ";
			//for (Iter it = _adj[v].begin(); it != _adj[v].end(); ++it) {
			for(uint w : _adj[v]) {
				o << w << " " << flush;
			}
			o << endl << flush;
		}
	}

private:
	void copia(const Grafo &other) {
		for (uint v = 0; v < V(); v++) {
			// recorrer adyacentes a v
			for (uint w : other.adj(v)) {
				_adj[v].push_back(w);
			}
		}
	}


};

/**
 * Para mostrar grafos por la salida estándar.
 */

inline ostream& operator<<(ostream& o,const Grafo& g){
	g.mostrar(o);
	return o;
}


class DepthFirstSearch {
private:
	bool* _marked;    // marked[v] = is there an s-v path?
	uint _count;      // number of vertices connected to s
	uint s;           // source vertex

	// depth first search from v
	void dfs(const Grafo& G, uint v) {
		_count++;
		_marked[v] = true;
		for (uint w : G.adj(v)) {
			if (!_marked[w]) {
				dfs(G, w);
			}
		}
	}

public:
	DepthFirstSearch(const Grafo& G, uint s) {
		_count = 0;
		_marked = new bool[G.V()];
		for(uint i = 0; i < G.V(); i++) _marked[i] = false;
		dfs(G, s);
	}

	~DepthFirstSearch() {
		delete[] _marked;
		_marked = NULL;
	}

	// is there an s-v path?
	bool marked(uint v) const {
		return _marked[v];
	}

	// number of vertices connected to s
	uint count() const {
		return _count;
	}

};

class DepthFirstPaths {
private:
	bool* marked;     // marked[v] = is there an s-v path?
	uint* edgeTo;     // edgeTo[v] = last edge on s-v path
	uint s;           // source vertex

	// depth first search from v
	void dfs(const Grafo& G, uint v) {
		marked[v] = true;
		for (uint w : G.adj(v)) {
			if (!marked[w]) {
				edgeTo[w] = v;
				dfs(G, w);
			}
		}
	}

public:
	DepthFirstPaths(const Grafo& G, uint s) : s(s) {
		edgeTo = new uint[G.V()];
		marked = new bool[G.V()];
		for(uint i = 0; i < G.V(); i++) marked[i] = false;
		dfs(G, s);
	}

	~DepthFirstPaths() {
		delete[] marked; marked = NULL;
		delete[] edgeTo; edgeTo = NULL;
	}

	// is there a path between s and v?
	bool hasPathTo(uint v) const {
		return marked[v];
	}

	// return a path between s and v; empty if no such path
	Path* pathTo(uint v) const {
		Path* path = new Path();
		if (!hasPathTo(v)) return path;
		for (uint x = v; x != s; x = edgeTo[x])
			path->push_front(x);
		path->push_front(s);
		return path;
	}


};

class BreadthFirstPaths {
private:
	bool* marked;     // marked[v] = is there an s-v path?
	uint* edgeTo;     // edgeTo[v] = last edge on s-v path
	uint* distTo;     // distTo[v] = number of edges shortest s-v path
	uint s;           // source vertex

	void bfs(const Grafo& G, uint s) {
		queue<uint> q;
		//for(uint v = 0; v < G.V(); v++) distTo[v] = numeric_limits<uint>::infinity();
		distTo[s] = 0;
		marked[s] = true;
		q.push(s);

		while (!q.empty()) {
			uint v = q.front(); q.pop();
			for (uint w : G.adj(v)) {
				if (!marked[w]) {
					edgeTo[w] = v;
					distTo[w] = distTo[v] + 1;
					marked[w] = true;
					q.push(w);
				}
			}
		}
	}

public:
	BreadthFirstPaths(const Grafo& G, uint s) : s(s) {
		edgeTo = new uint[G.V()];
		marked = new bool[G.V()];
		distTo = new uint[G.V()];
		for(uint i = 0; i < G.V(); i++) marked[i] = false;
		bfs(G, s);
	}

	~BreadthFirstPaths() {
		delete[] marked; marked = NULL;
		delete[] edgeTo; edgeTo = NULL;
		delete[] distTo; distTo = NULL;
	}

	// is there a path between s and v?
	bool hasPathTo(uint v) const {
		return marked[v];
	}

	// return a path between s to v; empty if no such path
	Path* pathTo(uint v) const {
		Path* path = new Path();
		if (!hasPathTo(v)) return path;
		for (uint x = v; x != s; x = edgeTo[x])
			path->push_front(x);
		path->push_front(s);
		return path;
	}

	uint distance(uint v) const {
		return distTo[v];
	}
	
};

class CC {
private:
	bool* marked;    // marked[v] = has vertex v been marked?
	uint* _id;       // id[v] = id of connected component containing v
	uint* _size;     // size[id] = number of vertices in given component
	uint _count;     // number of connected components

	// depth first search
	void dfs(const Grafo& G, uint v) {
		marked[v] = true;
		_id[v] = _count;
		_size[_count]++;
		//       for (int w : G.adj(v)) {
		for (uint w : G.adj(v)) {
			if (!marked[w]) {
				dfs(G, w);
			}
		}
	}

public:
	CC(const Grafo& G) {
		marked = new bool[G.V()];
		for(uint i = 0; i < G.V(); i++) marked[i] = false;
		_id = new uint[G.V()];
		_size = new uint[G.V()];
		for(uint i = 0; i < G.V(); i++) _size[i] = 0;
		_count = 0;
		for(uint v = 0; v < G.V(); v++) {
			if (!marked[v]) {
				dfs(G, v);
				_count++;
			}
		}
	}

	// id of connected component containing v
	uint id(int v) const {
		return _id[v];
	}

	// size of connected component containing v
	uint size(int v) const {
		return _size[_id[v]];
	}

	// number of connected components
	uint count() const {
		return _count;
	}

	// are v and w in the same connected component?
	bool areConnected(uint v, uint w) const {
		return id(v) == id(w);
	}

};

#endif /* GRAFO_H_ */
