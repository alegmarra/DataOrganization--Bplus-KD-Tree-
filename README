# TP DATOS 1C 2012 #

Se debera diseniar unsistema que sea capaz de realizar analisis y estadisticas sobre los accidentes y fallas en el mantenimiento de los trenes.

Se les pedira que generen un conjunto de datos con los siguientes campos:

1. Linea Ferroviaria
2. Franja horaria del siniestro
3. Fall
4. Accidente
5. Formacion

En caso de lineas ferroviarias algunos ejemplos pueden ser: Bolgrano norte, Roca, Sarmiento, Mitre, etc.

Ejemplos de franjas horarias: 00:00 - 00:30 21/02/2012, 19:30 - 20:00 03/04/2012.

Fallas: no cierra puertas, cierran 50%, cierran 80%, enganchan mal los vagones, no frena, frena 50%, frena 80%, asientos rotos 20%, asientos rotos 50%, asientos rotos 80%, motores al 30%, motores al 50%, motores al 80%, etc.

Accidentes: choque con otra formacion, incendio, choque con estacion, descarrilado, desacoplado, no enciende, se corto la energia en un tramo, etc.

Formaciones: 0001, 0256, 0698, 9602, etc

Nos interesa descubrir:

1. Todos los trenes que tienen cierta falla.
2. Todos los trenes que tienen cierto accidente.
3. Todas las fallas de una formacion determinada.
4. Todos los accidentes de una formacion determinada.
5. Todas las fallas.
6. Todas las formaciones.
7. Todas las lineas.
8. Todos los accidentes

Los puntos del 1 a 4 deberian ofrecer la posibilidad de filtrarlos por rango de fechas

Para la resolucion del trabajo practico s e debera implementar un kd-tree que permita indexar sobre un B+.

La idea es adaptar el B+ para realizar busquedas multidimensionales. Para ello se divide al arbol en niveles, cada uno de los cuales contiene nodos con valores de una de las dimensiones que componen la clave multiple. La asignacion del atributo a usar en cada nivel se realiza utilizando el algoritmo Round Robin sobre el total de atributos de la clave compuesta.

