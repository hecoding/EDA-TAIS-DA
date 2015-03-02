(Tema Diseño e implementación de TADs arborescentes, año 2013/2014, ejercicio 9)

Extiende la implementación de los árboles binarios con la siguiente operación:
``` cpp
/∗∗
Devuelve true si el árbol binario cumple las propiedades
de los árboles ordenados: la raíz es mayor que todos los elementos
del hijo izquierdo y menor que los del hijo derecho y tanto el
hijo izquierdo como el derecho son ordenados.
∗/
template <class T>
bool Arbin::esOrdenado() const;
```
Implementa la misma operación como función externa al TAD.
