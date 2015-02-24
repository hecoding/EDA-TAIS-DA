#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>

template <typename Object>
class Matriz {
private:
    std::vector<std::vector<Object>> datos;

public:
	std::size_t numfils() const { return datos.size(); }
	std::size_t numcols() const { return numfils() > 0 ? datos[0].size() : 0; }

    Matriz(int fils, int cols) : datos(fils, std::vector<Object> (cols)) {}

    const std::vector<Object>& operator[] (std::size_t f) const {

        return datos[f];
    }

    std::vector<Object> & operator[](std::size_t f) {

        return datos[f];
    }
};

#endif


