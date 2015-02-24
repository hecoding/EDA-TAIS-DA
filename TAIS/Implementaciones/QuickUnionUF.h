/*
 * QuickUnionUF.h
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
public:
    // instantiate N isolated components 0 through N-1
   QuickUnionUF(int N) : size(N), _count(size), id(new int[size]) {
        for (int i = 0; i < N; i++)
            id[i] = i;
    }

    // return number of connected components
    int count() const {
        return _count;
    }

    //  return root of component corresponding to element p
    int find(int p) const {
        while (p != id[p])
            p = id[p];
        return p;
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
        id[i] = j;
        _count--;
    }

};


#endif /* QUICKUNIONUF_H_ */
