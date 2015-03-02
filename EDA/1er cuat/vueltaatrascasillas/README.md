(Tema vuelta atrás, año 2013/2014, ejercicio 6. aka ejercicio de vuelta atrás examen EDA Junio 2012)   

[Examen Junio, 2012] Implementar una función que encuentre la forma más rápida de viajar desde una casilla de salida hasta una casilla de llegada de una rejilla. Cada casilla de la rejilla está etiquetada con una letra, de forma que en el camino desde la salida hacia la llegada se debe ir formando (de forma cíclica) una palabra dada. Desde una celda se puede ir a cualquiera de las cuatro celdas adyacentes.   

Como ejemplo, a continuación aparece la forma más corta de salir de una rejilla de 5 × 8 en la que el punto de salida está situado en la posición (0, 4) y hay que llegar a la posición (7, 0) y la palabra que hay que ir formando por el camino es `EDA`.

<img src="http://s12.postimg.org/8oxbjdljh/image.jpg" width="450px" >

Para la implementación puedes suponer la existencia de dos variables globales `N` y `M` que determinan el tamaño de la rejilla, así como la información de la propia rejilla, `char lab[N][M]`;   
También puedes suponer la existencia de una variable global que contiene la palabra a utilizar, `Lista<char> palabra`;   
Las función recibirá el punto origen y el punto destino y deberá determinar la forma más rápida de viajar de uno a otro (si es que esto es posible), dando las direcciones que hay que ir cogiendo (en el caso del ejemplo será `E, N, E, E, E, etc.)`. Si necesitas parámetros adicionales, añádelos indicando sus valores iniciales.
