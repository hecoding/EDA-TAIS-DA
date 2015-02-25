#Práctica de grafos
Se valorará tanto la *correción* como la *eficiencia* y la *simplicidad* de la solución propuesta.

Consideremos el siguiente juguete. Cada rueda tiene en su periferia del 0 al 9 dispuestos de forma consecutiva (en el sentido de las agujas del reloj). Los números superiores de las cuatro ruedas forman un entero de cuatro dígitos. Por ejemplo, en la siguente figura se forma el número 8.056. Cada rueda tiene asociados dos botones. Si se pulsa el botón marcado con <-- la rueda gira una posición en el sentido de las agujas del reloj, mientras que si se pulsa el botón marcado con --> el giro se produce en la dirección opuesta.

![imagen juguete](http://imgbin.org/images/22525.png "Juguete de ruedas")

Comenzaremos con una configuración inicial de las ruedas, de forma que sus dígitos superiores forman el entero *I1 I2 I3 I4*. Además habrá un número *n* de configuraciones prohibidas *Pi1 Pi2 Pi3 Pi4* *(1 <= i <= n)* y una configuración final *T1 T2 T3 T4*. La práctica consiste en escribir un programa que calcule el número mínimo de pulsaciones necesarias para transformar la configuración inicial en la final, sin pasar por ninguna de las prohibidas.

####Entrada
La primera línea de la entrada contiene un entero *N*, que determina el número de problemas a resolver. Le sigue una línea en blanco. La primera línea de cada caso contiene la configuración inicial, especificada por cuatro dígitos. Hay un espacio en blanco entre cada dos dígitos consecutivos. La siguiente línea muestra la configuración final. La tercera línea contiene un entero *n*, que indica el número de configuraciones prohibidas. Cada una de las siguientes *n* líneas contiene una configuración prohibida. Hay una línea en blanco entre cada dos casos de prueba consecutivos.

####Salida
Para cada caso de prueba se debe mostrar una línea que contenga el número mínimo de pulsaciones requeridas. Si no es posible llegar a la configuración final se debe imprimir `-1`.

####Ejemplo de entrada
2   
8 0 5 6   
6 5 0 8   
5   
8 0 5 7   
8 0 4 7   
5 5 0 8   
7 5 0 8   
6 4 0 8   
<br/>
0 0 0 0   
5 3 1 7   
8   
0 0 0 1   
0 0 0 9   
0 0 1 0   
0 0 9 0   
0 1 0 0   
0 9 0 0   
1 0 0 0   
9 0 0 0   

####Salida correspondiente
14   
-1
