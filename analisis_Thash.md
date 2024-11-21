# Análisis de tablas de dispersión

* *Autor: Francisco Jose Cabrera Bermejo*

## Tamaño de tabla: 15478
| función               | máximo de colisiones | factor de carga | promedio de colisiones |
|-----------------------|:--------------------:|:---------------:|:----------------------:|
| Dispersion cuadratica |          19          |    0.646143     |        0.688331        |
| Dispersion doble 1    |          12          |    0.646143     |        0.614439        |
| Dispersion doble 2    |          12          |    0.646143     |        0.60484        |


## Tamaño de tabla: 14795
| función               | máximo de colisiones | factor de carga | promedio de colisiones |
|-----------------------|:--------------------:|:---------------:|:----------------------:|
| Dispersion cuadratica |          16          |    0.675972     |        0.785221       |
| Dispersion doble 1    |          16          |    0.675972     |        0.668433        |
| Dispersion doble 2    |          15          |    0.675972     |        0.682532        |

## Justificación de la configuración elegida
Hemos optado por ... por elegir la función de dispersion doble 2 con lambda 0.65,
esta decision es tomada ya que es la función que da un menor número máximo de 
colisiones, junto a un menor factor de carga y un menor promedio de colisiones.

Es importante destacar y explicar porque se ha elegido esta función, en este caso,
al tener un menor valor máximo de colisiones se consigue una mejor dispersion y un
menor caso de colisiones dadas, al tener un promedio menor de colisiones que el 
resto de funciones, indica que los datos se distribuyen de manera más uniforme 
en la tabla que si aplicásemos el resto de funciones. Por último, también es 
importante que nuestra función tenga un menor factor de carga (oscila entre 0 y 1),
ya que un valor cercano a 1 implica una mayor probabilidad de colisiones ya que la
tabla esta más llena.

## Resultados obtenidos al realizar la busqueda con un vector y con un mapa
Con un vector hemos tardado en realizar la busqueda: 0.021
Con una lista hemos tardado en realizar la busqueda: 0.018
