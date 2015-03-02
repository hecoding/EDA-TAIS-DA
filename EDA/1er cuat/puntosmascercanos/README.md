# El problema del par más cercano (closest pair)
+ Dada una nube de n puntos en el plano, *n ≥ 2*, se trata de encontrar el par de puntos cuya distancia euclídea es menor (si hubiera más de un par con esa distancia mínima, basta con devolver uno de ellos). El problema tiene interés práctico. Por ejemplo, en un sistema de control del tráfico aéreo, el par más cercano nos informa del mayor riesgo de colisión entre dos aviones.

+ Dados p dos puntos, *p1 = (x1, y1 )* y *p2 = (x2, y2)*, su distancia euclídea viene dada por *d = sqrt( (x1 − x2)^2 + (y1 − y2)^2 )* . El algoritmo de “fuerza bruta” calcularía la distancia entre todo posible par de puntos, y devolvería el mínimo de todas ellas. Como hay *1/2 * n(n − 1)* pares posibles, el coste resultante sería **cuadrático**.

+ El enfoque DV trataría de encontrar el par más cercano a partir de los pares más cercanos de conjuntos de puntos que sean una fracción del original. Una posible estrategia es:
  + Dividir Crear dos nubes de puntos de tamaño mitad. Podríamos ordenar los puntos por la coordenada *x* y tomar la primera mitad como nube izquierda *I*, y la segunda como nube derecha *D*. Determinamos una linea vertical imaginaria *l* tal que todos los puntos de *I* están sobre *l*, o a su izquierda, y todos los de *D* están sobre *l*, o a su derecha.
  + Conquistar Resolver recursivamente los problemas *I* y *D*. Sean *δI* y *δD* las respectivas distancias mínimas encontradas y sea *δ = ḿın(δI, δD)*.
  + Combinar El par más cercano de la nube original, o bien es el par con distancia *δ*, o bien es un par compuesto por un punto de la nube *I* y otro punto de la nube *D*. En ese caso, ambos puntos se hallan a lo sumo a una distancia *δ* de *l*. La operación *combinar* debe investigar los puntos de dicha banda vertical.

+ Antes de seguir con los detalles, debemos investigar el coste esperado de esta estrategia. Como el algoritmo fuerza-bruta tiene coste *Θ(n^2)*, trataremos de conseguir un coste *Θ(nlog n)* en el caso peor. Sabemos por la experiencia de algoritmos como mergesort que ello exige unos parámetros *a = 2*, *b = 2*, *k = 1*, en decir tan solo podemos consumir un coste lineal en las operaciones de dividir y combinar.

+ La ordenación de los puntos por la coordenada de x se puede realizar una sola vez al principio (es decir, fuera del algoritmo recursivo DV) con un coste *Θ(nlog n)* en el caso peor, lo que es admisible para mantener nuestro coste total. Una vez ordenada la nube, la división en dos puede conseguirse con coste constante o lineal, dependiendo de si se utilizan vectores o listas como estructuras de datos de la implementación.

+ Una vez resueltos los dos subproblemas, se pueden filtrar los puntos de *I* y *D* para conservar sólo los que estén en la banda vertical de anchura *2δ* y centrada en *l*. El filtrado puede hacerse con coste lineal. Llamemos *BI* y *BD* a los puntos de dicha banda respectivamente a la izquierda y a la derecha de *l*.

+ Para investigar si en la banda hay dos puntos a distancia menor que *δ*, aparentemente debemos calcular la distancia de cada punto de *BI* a cada punto de *BD*. Es fácil construir nubes de puntos en las que todos ellos caigan en la banda tras el filtrado, de forma que en el caso peor podríamos tener *|BI| = |BD| = n/2* . En ese caso, el cálculo de la distancia mínima entre los puntos de la banda sería cuadrático, y el coste total del algoritmo DV también.

+ Demostraremos que basta ordenar por la coordenada y el conjunto de puntos *BI ∪ BD* y después recorrer la lista ordenada comparando cada punto **con los 7 que le siguen**. Si de este modo no se encuentra una distancia menor que *δ*, concluimos que todos los puntos de la banda distan más entre sí. Este recorrido es claramente de coste lineal.

+ Suponiendo que esta estrategia fuera correcta, todavía quedaría por resolver la ordenación por la coordenada *y*. Si ordenáramos *BI ∪ BD* en cada llamada recursiva, gastaríamos un coste *Θ(nlog n)* en cada una, lo que conduciría un coste total en *Θ(nlog^2 n)*.

+ Recordando la técnica de los *resultados acumuladores*, podemos exigir que cada llamada recursiva devuelva un resultado extra: la lista de sus puntos ordenada por la coordenada *y*. Este resultado puede propagarse hacia arriba del árbol de llamadas con un coste lineal, porque basta aplicar el algoritmo de mezcla de dos listas ordenadas. La secuencia de acciones de la operación combinar es entonces la siguiente:
  1. Realizar la mezcla ordenada de las dos listas de puntos devueltas por las llamadas recursivas. Esta lista se devolverá al llamante.
  2. Filtrar la lista resultante, conservando los puntos a una distancia de la línea divisoria *l* menor o igual que *δ*. Llamemos *B* a la lista filtrada.
  3. Recorrer *B* calculando la distancia de cada punto a los 7 que le siguen, comprobando si aparece una distancia menor que *δ*.
  4. Devolver los dos puntos a distancia mínima, considerando los tres cálculos realizados: parte izquierda, parte derecha y lista *B*.

####Corrección
<img src="http://s11.postimg.org/lq7vvedur/image.jpg" width="500px" >
+ Consideremos un rectángulo cualquiera de anchura *2δ* y altura *δ* centrado en la línea divisoria *l*. Afirmamos que, contenidos en él, puede haber a lo sumo 8 puntos de la nube original. En la mitad izquierda puede haber a lo sumo 4, y en caso de haber 4, situados necesariamente en sus esquinas, y en la mitad derecha otros 4, también en sus esquinas. Ello es así porque, por hipótesis de inducción, los puntos de la nube izquierda están separados entre sí por una distancia de al menos δ, e igualmente los puntos de la nube derecha entre sí. En la línea divisoria podrían coexistir hasta dos puntos de la banda izquierda con dos puntos de la banda derecha.
+ Si colocamos dicho rectángulo con su base sobre el punto *p1* de menor coordenada y de *B*, estamos seguros de que a los sumo los 7 siguientes puntos de *B* estarán en dicho rectángulo. A partir del octavo, él y todos los demás distarán más que *δ* de *p1* . Desplazando ahora el rectángulo de punto a punto, podemos repetir el mismo razonamiento. No es necesario investigar los puntos con menor coordenada y que el punto en curso, porque esa comprobación ya se hizo cuando se procesaron dichos puntos.
+ Elegimos como caso base de la inducción *n < 4*. De este modo, al subdividir una nube con *n ≥ 4* puntos, nunca generaremos problemas con un solo punto.
