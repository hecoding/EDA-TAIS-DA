/*
 * QuickFindUF.h
 *
 *  Created on: 24/10/2012
 *      Author: Alberto Verdejo
 */

#ifndef QUICKFINDUF_H_
#define QUICKFINDUF_H_

class QuickFindUF {
private:
   int size;
   int _count;
   int* id;
public:
    // instantiate N isolated components 0 through N-1
     QuickFindUF(int N) : size(N), _count(size), id(new int[size]) {
        for (int i = 0; i < N; i++)
            id[i] = i;
    }

    // return number of connected components
    int count() const {
        return _count;
    }

    // Return component identifier for component containing p
    int find(int p) const {
        return id[p];
    }

    // are elements p and q in the same component?
    bool connected(int p, int q) const {
        return id[p] == id[q];
    }

    // merge components containing p and q
    void unir(int p, int q) {
        if (connected(p, q)) return;
        int pid = id[p];
        for (int i = 0; i < size; i++)
            if (id[i] == pid) id[i] = id[q];
        _count--;
    }

};


#endif /* QUICKFINDUF_H_ */
