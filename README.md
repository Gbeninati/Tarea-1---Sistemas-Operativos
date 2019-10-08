# Tarea-1---Sistemas-Operativos
Tarea 1 de sistemas operativos con la utilización de pipes y forks

Integrantes:
- Gianni Beninati
- David Monsalves

Avances de cada integrante:

AVANCE 1

Funciones de Gianni :
- crear_directorios
- crear_0
- crear_numeros1_9
- crear_especiales
- mover_archivo

Funciones David:
- escoger_carta_random
- repartir_cartas
- ver_archivos
- encontrar_carta
- tirar_carta
- eliminar_carta

Consideraciones:
- El primer avance crea las 108 cartas y los directorios Mazo, Juego, Jugador1, Jugador2, Jugador3 y Jugador 4, y reparte 7 cartas al azar a cada jugador.
- Se incluyen otras funciones para listar los archivos de un directorio, eliminar un archivo y jugar una carta. Todas estas se utilizaran en un futuro.
- Se recomienda correr el programa en Linux

AVANCE 2


Consideraciones:
- Para el avance 2 se realizaron 2 archivos: avance2a.c y avance2b.c


Consideraciones Avance2a:
- El avance2a incluye las reglas del juego y permite que un solo jugador juegue contra el mismo
- Al tirar un cambio de color y luego un +4, el programa se cae, se arreglara esto para la entrega final
- Este archivo se encuntra en la carpera Avance2a


Consideraciones Avance2b:
- El avance2b se enfoca en el uso de pipes y comunica a cada proceso si es o no su turno. El programa crea 3 procesos hijos y de manera ciclica pasa de turno, imprimiendo el jugador que se encuentra en el turno actual (cada proceso es un jugador). Se comienza con el Jugador 1, luego se continua al 2 y asi sucesivamente hasta completar un ciclo. Cuando es el turno del Jugador 1 nuevamente, se pregunta si se quiere cambiar de rumbo (opcion 1), continuar con el rumbo actual (opcion 2), o terminar el programa (opcion 0). Si se cambia el rumbo, el siguiente Jugador es el 4, luego 3, continuando.


Instrucciones para correr avance2a:
- Dirigirse al directorio Avance2a
- Abrir el terminal en el directorio en que se encuentra el archivo
- Escribir comando: make


Instrucciones para correr avance2b:
- Dirigirse al directorio Avance2b
- Abrir el terminal en el directorio en que se encuentra el archivo
- Escribir comando: make
