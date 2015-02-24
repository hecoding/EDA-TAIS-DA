/*
 * GrafoDirigido.h
 *
 *  Created on: 17/10/2012
 *      Author: Alberto Verdejo
 */

#ifndef GRAFODIRIGIDO_H_
#define GRAFODIRIGIDO_H_

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


class GrafoDirigido {

private:
	uint _V;      // número de vértices
	uint _E;      // número de aristas
	Adys* _adj;   // vector de listas de adyacencia

public:

	/**
	 * Crea un grafo aleatorio con V vértices y E aristas.
	 */
	GrafoDirigido(uint v, uint e=0) : _V(v), _E(0), _adj(new Adys[_V]) {
		for (uint i = 0; i < e; i++) {
			uint v = rand() % _V; uint w = v;
			while(w == v) w = rand() % _V;
			ponArista(v, w);
		}
	}

	/**
	 * Crea un grafo a partir de un fichero de entrada.
	 */
	GrafoDirigido(string file) {
		ifstream ent(file.c_str());
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

	~GrafoDirigido(){
		delete[] _adj;
		_adj = NULL;
	}

	/**
	 * Constructor de copia.
	 */
	GrafoDirigido(const GrafoDirigido& G)  : _V(G.V()), _E(G.E()), _adj(new Adys[_V]) {
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
	 * Return the reverse of the digraph.
	 */
	GrafoDirigido reverse() const {
		GrafoDirigido R(_V);
		for (uint v = 0; v < _V; v++) {
			for (uint w : _adj[v]) {
				R.ponArista(w, v);
			}
		}
		return R;
	}

	/**
	 * Muestra el grafo en el stream de salida o
	 */
	void mostrar(ostream& o) const {
		o << _V << " vertices, " << _E << " aristas" << endl;
		for (uint v = 0; v < _V; v++) {
			o << v << ": ";
			for(uint w : _adj[v]) {
				o << w << " " << flush;
			}
			o << endl << flush;
		}
	}

private:
	void copia(const GrafoDirigido &other) {
		for (uint v = 0; v < V(); v++) {
			// recorrer adyacentes a v
			for (uint w : other.adj(v)) {
				_adj[v].push_back(w);
			}
		}
	}

};

/**
 * Para mostrar grafos por la salida estándar
 */
inline ostream& operator<<(ostream& o,const GrafoDirigido& g){
	g.mostrar(o);
	return o;
}

class DepthFirstDirectedPaths {
private:
	bool* marked;     // marked[v] = is there an s-v path?
	uint* edgeTo;     // edgeTo[v] = last edge on s-v path
	uint s;           // source vertex

	// depth first search from v
	void dfs(const GrafoDirigido& G, uint v) {
		marked[v] = true;
		for (uint w : G.adj(v)) {
			if (!marked[w]) {
				edgeTo[w] = v;
				dfs(G, w);
			}
		}
	}

public:
	DepthFirstDirectedPaths(const GrafoDirigido& G, uint s) : s(s) {
		edgeTo = new uint[G.V()];
		marked = new bool[G.V()];
		for(uint i = 0; i < G.V(); i++) marked[i] = false;
		dfs(G, s);
	}

	~DepthFirstDirectedPaths() {
		delete[] marked; marked = NULL;
		delete[] edgeTo; edgeTo = NULL;
	}

	// is there a path between s and v?
	bool hasPathTo(uint v) const {
		return marked[v];
	}

	// return a path between s to v; null if no such path
	Path* pathTo(uint v) const {
		Path* path = new Path();
		if (!hasPathTo(v)) return path;
		for (uint x = v; x != s; x = edgeTo[x])
			path->push_front(x);
		path->push_front(s);
		return path;
	}
};


class BreadthFirstDirectedPaths {
private:
	bool* marked;     // marked[v] = is there an s-v path?
	uint* edgeTo;     // edgeTo[v] = last edge on s-v path
	uint* distTo;     // distTo[v] = number of edges shortest s-v path
	//	uint s;           // source vertex

	// BFS from single source
	void bfs(const GrafoDirigido& G, uint s) {
		queue<uint> q;
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

	// BFS from multiple sources
	void bfs(const GrafoDirigido& G, const list<uint>& sources) {
		queue<uint> q;
		for(uint s : sources) {
			distTo[s] = 0;
			marked[s] = true;
			q.push(s);
		}

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
	// single source
	BreadthFirstDirectedPaths(const GrafoDirigido& G, uint s) {
		edgeTo = new uint[G.V()];
		marked = new bool[G.V()];
		distTo = new uint[G.V()];
		for(uint i = 0; i < G.V(); i++) marked[i] = false;
	//	for(uint v = 0; v < G.V(); v++) distTo[v] = numeric_limits<uint>::infinity();
		bfs(G, s);
	}

	// multiple source
	BreadthFirstDirectedPaths(const GrafoDirigido& G, const list<uint>& sources) {
		edgeTo = new uint[G.V()];
		marked = new bool[G.V()];
		distTo = new uint[G.V()];
		for(uint i = 0; i < G.V(); i++) marked[i] = false;
		//for(uint v = 0; v < G.V(); v++) distTo[v] = numeric_limits<uint>::infinity();
		bfs(G, sources);
	}

	~BreadthFirstDirectedPaths() {
		delete[] marked; marked = NULL;
		delete[] edgeTo; edgeTo = NULL;
		delete[] distTo; distTo = NULL;
	}

	// length of shortest path from s (or sources) to v
	uint distance(uint v) const {
		return distTo[v];
	}

	// is there a path between s and v?
	bool hasPathTo(uint v) const {
		return marked[v];
	}

	// return a path between s and v; empty if no such path
	Path* pathTo(uint v) const {
		Path* path = new Path();
		if (!hasPathTo(v)) return path;
		uint x;
		for (x = v; distTo[x] != 0; x = edgeTo[x])
			path->push_front(x);
		path->push_front(x);
		return path;
	}

};


class DepthFirstOrder {
private:
	bool* marked;           // marked[v] = has v been marked in dfs?
	int* pre;               // pre[v]    = preorder  number of v
	int* post;              // post[v]   = postorder number of v
	list<uint> preorder;    // vertices in preorder
	list<uint> postorder;   // vertices in postorder
	list<uint> revPost;     // vertices in reverse postorder
	uint preCounter;        // counter or preorder numbering
	uint postCounter;       // counter for postorder numbering

	// run DFS in digraph G from vertex v and compute preorder/postorder
	void dfs(const GrafoDirigido& G, uint v) {
		marked[v] = true;
		pre[v] = preCounter++;
		preorder.push_back(v);
		for (uint w : G.adj(v)) {
			if (!marked[w]) {
				dfs(G, w);
			}
		}
		postorder.push_back(v);
		post[v] = postCounter++;
		revPost.push_front(v);
	}

public:
	// depth-first search preorder and postorder in a digraph
	DepthFirstOrder(const GrafoDirigido& G) {
		pre    = new int[G.V()]; preCounter = 0;
		post   = new int[G.V()]; postCounter = 0;
		marked    = new bool[G.V()];
		for (uint v = 0; v < G.V(); v++) marked[v] = false;
		for (uint v = 0; v < G.V(); v++)
			if (!marked[v]) dfs(G, v);
	}

	int prenum(int v) const {
		return pre[v];
	}

	int postnum(int v) const {
		return post[v];
	}

	// return vertices in postorder as an Iterable
	const list<uint>& postOrder() const {
		return postorder;
	}

	// return vertices in postorder as an Iterable
	const list<uint>& preOrder() const {
		return preorder;
	}

	// return vertices in reverse postorder as an Iterable
	const list<uint>& reversePost() const {
		return revPost;
	}

};


class DirectedCycle {
private:
	bool* marked;        // marked[v] = has vertex v been marked?
	int* edgeTo;         // edgeTo[v] = previous vertex on path to v
	bool* onStack;       // onStack[v] = is vertex on the stack?
	list<uint> ciclo;   // directed cycle (or null if no such cycle)
	bool hayciclo;

	// check that algorithm computes either the topological order or finds a directed cycle
	void dfs(const GrafoDirigido& G, int v) {
		onStack[v] = true;
		marked[v] = true;
		for (uint w : G.adj(v)) {
			// short circuit if directed cycle found
			if (hayciclo) return;
			//found new vertex, so recur
			else if (!marked[w]) {
				edgeTo[w] = v;
				dfs(G, w);
			}
			// trace back directed cycle
			else if (onStack[w]) {
				hayciclo = true;
				for (uint x = v; x != w; x = edgeTo[x]) {
					ciclo.push_front(x);
				}
				ciclo.push_front(w);
				ciclo.push_front(v);
			}
		}
		onStack[v] = false;
	}

public:
	DirectedCycle(const GrafoDirigido& G) {
		hayciclo = false;
		marked  = new bool[G.V()];
		for (uint v = 0; v < G.V(); v++) marked[v] = false;
		onStack = new bool[G.V()];
		for (uint v = 0; v < G.V(); v++) onStack[v] = false;
		edgeTo  = new int[G.V()];
		for (uint v = 0; v < G.V(); v++)
			if (!marked[v]) dfs(G, v);
	}

	bool hasCycle() const { return hayciclo; }
	const list<uint>& cycle() const { return ciclo; }
};


class Topological {
private:
	list<uint> _order;    // topological order
	bool hayOrden;
public:
	// topological sort in a digraph
	Topological(const GrafoDirigido& G) {
		DirectedCycle finder(G);
		if (!finder.hasCycle()) {
			hayOrden = true;
			DepthFirstOrder dfs(G);
			_order = dfs.reversePost();
		} else hayOrden = false;
	}

	// return topological order if a DAG; null otherwise
	const list<uint>& order() const {
		return _order;
	}

	// does digraph have a topological order?
	bool hasOrder() const {
		return hayOrden;
	}
};


class KosarajuSharirSCC {
private:
	bool* marked;     // marked[v] = has vertex v been visited?
	int* _id;         // id[v] = id of strong component containing v
	int _count;       // number of strongly-connected components

	// DFS on graph G
	void dfs(const GrafoDirigido& G, uint v) {
		marked[v] = true;
		_id[v] = _count;
		for (uint w : G.adj(v)) {
			if (!marked[w]) dfs(G, w);
		}
	}

public:
	KosarajuSharirSCC(const GrafoDirigido& G) {

		// compute reverse postorder of reverse graph
		DepthFirstOrder dfsrev(G.reverse());

		// run DFS on G, using reverse postorder to guide calculation
		marked = new bool[G.V()];
		for (uint v = 0; v < G.V(); v++) marked[v] = false;
		_id = new int[G.V()];
		_count = 0;

		for (uint v : dfsrev.reversePost()) {
			if (!marked[v]) {
				dfs(G, v);
				_count++;
			}
		}
	}

	// return the number of strongly connected components
	int count() const { return _count; }

	// are v and w strongly connected?
	bool stronglyConnected(int v, int w) const {
		return _id[v] == _id[w];
	}

	// id of strong component containing v
	int id(int v) const {
		return _id[v];
	}
};

#endif /* GRAFODIRIGIDO_H_ */
