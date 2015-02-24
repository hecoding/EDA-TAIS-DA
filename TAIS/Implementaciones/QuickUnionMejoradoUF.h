/*
 * QuickUnionMejoradoUF.h
 *
 *  Created on: 24/10/2012
 *      Author: Alberto Verdejo
 */

#ifndef QUICKUNIONUF_H_
#define QUICKUNIONUF_H_

class QuickUnionUF {
private:
   int size;
   int _count;
   int* id;
   int* sz;
public:
    // instantiate N isolated components 0 through N-1
   QuickUnionUF(int N) : size(N), _count(size), id(new int[size]), sz(new int[size]) {
        for (int i = 0; i < N; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }

    // return number of connected components
    int count() const {
        return _count;
    }

    //  return root of component corresponding to element p
    int find(int p) const {
        int root = p;
         while (root != id[root])
             root = id[root];
         while (p != root) {
             int newp = id[p];
             id[p] = root;
             p = newp;
         }
         return root;
    }

    // are elements p and q in the same component?
    bool connected(int p, int q) const {
        return find(p) == find(q);
    }

    // merge components containing p and q
    void unir(int p, int q) {
        int i = find(p);
        int j = find(q);
        if (i == j) return;
        // make smaller root point to larger one
        if   (sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i]; }
        else                 { id[j] = i; sz[i] += sz[j]; }
        _count--;
    }

};


#endif /* QUICKUNIONUF_H_ */
