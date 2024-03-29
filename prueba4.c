#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

//Funcion que crea las cartas del 1-9
void crear_numeros1_9(){
  char colores[8][25] = {" rojo.txt"," azul.txt"," amarillo.txt"," verde.txt", " rojo (2).txt"," azul (2).txt"," amarillo (2).txt"," verde (2).txt"};
  int i;
  for(i = 0; i < 8; i++){
    int numero = 1; //Primero se crean todas las cartas 1's de distintos colores, despues las 2's y asi sucesivamente
    while(numero < 10){
      char directorio[50] = "Mazo/"; //Directorio en donde se guardan las cartas
      char n[2];
      sprintf(n,"%d", numero); //El entero numero se transforma a string
      strcat(directorio,n); //Se concatena el string directorio con el numero de la carta y se guarda en el string directorio
      strcat(directorio,colores[i]); //Se concatena nuevamente el string directorio (este ya fue concatenado con el numero) con el color, quedando de la forma Mazo/numero color.txt
      FILE *fp = fopen(directorio,"a"); //Se  crea el archivo de la carta
      fclose(fp);
      numero++;
    }
  }
}

//Funcion que crea las cartas 0's
void crear_0(){
  char colores[4][25] = {" rojo.txt"," azul.txt"," amarillo.txt"," verde.txt"};
  int i;
  for(i = 0; i < 4; i++){
    char directorio[30] = "Mazo/0";
    strcat(directorio,colores[i]);
    FILE *fp = fopen(directorio,"a");
    fclose(fp);
  }
}


//Funcion para crear todos los directorios a utillizar
void crear_directorios(){
  mkdir("Mazo",0700);
  mkdir("Jugador1",0700);
  mkdir("Jugador2",0700);
  mkdir("Jugador3",0700);
  mkdir("Jugador4",0700);
  mkdir("Juego",0700);
}

//Funcion que crea todas cartas que no son numeros
void crear_especiales(){
  char colores[8][25] = {" rojo.txt"," azul.txt"," amarillo.txt"," verde.txt", " rojo (2).txt"," azul (2).txt"," amarillo (2).txt"," verde (2).txt"};
  int i;
  for(i = 0; i < 8; i++){
    char directorio[30] = "Mazo/+2";
    char directorio2[30] = "Mazo/reversa";
    char directorio3[30] = "Mazo/salto";
    strcat(directorio,colores[i]);
    strcat(directorio2,colores[i]);
    strcat(directorio3,colores[i]);
    FILE *fp = fopen(directorio,"a");
    FILE *fp2 = fopen(directorio2,"a");
    FILE *fp3 = fopen(directorio3,"a");
    fclose(fp);
    fclose(fp2);
    fclose(fp3);
  }
  for(i = 0; i < 4; i++){
    char directorio[30] = "Mazo/+4.txt";
    char directorio2[30] = "Mazo/+4 (2).txt";
    char directorio3[30] = "Mazo/+4 (3).txt";
    char directorio4[30] = "Mazo/+4 (4).txt";
    char directorio5[30] = "Mazo/cambio color.txt";
    char directorio6[30] = "Mazo/cambio color (2).txt";
    char directorio7[30] = "Mazo/cambio color (3).txt";
    char directorio8[30] = "Mazo/cambio color (4).txt";
    FILE *fp = fopen(directorio,"a");
    FILE *fp2 = fopen(directorio2,"a");
    FILE *fp3 = fopen(directorio3,"a");
    FILE *fp4 = fopen(directorio4,"a");
    FILE *fp5 = fopen(directorio5,"a");
    FILE *fp6 = fopen(directorio6,"a");
    FILE *fp7 = fopen(directorio7,"a");
    FILE *fp8 = fopen(directorio8,"a");
    fclose(fp);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    fclose(fp6);
    fclose(fp7);
    fclose(fp8);
  }
}

//Funcion que mueve un archivo de un directorio origen (directorio_origen) a uno de destino (directorio_destino)
void mover_archivo(char directorio_origen[30], char directorio_destino[30]){
  rename(directorio_origen,directorio_destino);
}

//Funcion que lista en pantalla todos los archivos del directorio entregado
void ver_archivos(char directorio[30]){
  DIR *d;
  struct dirent *dir;
  d = opendir(directorio);
  if (d){
      while ((dir = readdir(d)) != NULL){
        if (dir->d_type == DT_REG){
          printf("%s\n", dir->d_name);
        }
      }
      closedir(d);
    }
}

//Funcion que recibe un directorio y un entero n, y entrega el archivo n-esimo de ese directorio
char * encontrar_carta(char directorio[30],int n){
  DIR *d;
  int i = 0;
  static char carta[40];
  struct dirent *dir;
  d = opendir(directorio);
  if (d){
      while ((dir = readdir(d)) != NULL){
        if (dir->d_type == DT_REG){
          if(i == n){
          strcpy(carta,dir->d_name);
          break;
        }
          i++;
      }
    }
      closedir(d);
    }
  return carta;
  }

//Funcion que retorna una carta al azar desde el mazo con "tamanio" cantidad de cartas
char* escoger_carta_random(int tamanio){
  srand(time(NULL));
  int n = rand() % tamanio;
  char *carta;
  carta = encontrar_carta("Mazo", n);
  return carta;
}

//Funcion que reparte 7 cartas al azar a cada jugador. Mueve las cartas desde el directorio Mazo ak directorio del jugador
  void repartir_cartas(){
    int cont_tamanio = 0;
    int cont_cartas = 0;
    char *carta;
    while (cont_cartas < 7){
      carta = escoger_carta_random(107-cont_tamanio);
      char origen[50] = "Mazo/";
      char destino[50] = "Jugador1/";
      strcat(origen,carta);
      strcat(destino,carta);
      mover_archivo(origen,destino);
      cont_cartas++;
      cont_tamanio++;
    }
    cont_cartas = 0;
    while (cont_cartas < 7){
      carta = escoger_carta_random(107-cont_tamanio);
      char origen[50] = "Mazo/";
      char destino[50] = "Jugador2/";
      strcat(origen,carta);
      strcat(destino,carta);
      mover_archivo(origen,destino);
      cont_cartas++;
      cont_tamanio++;
    }
    cont_cartas = 0;
    while (cont_cartas < 7){
      carta = escoger_carta_random(107-cont_tamanio);
      char origen[50] = "Mazo/";
      char destino[50] = "Jugador3/";
      strcat(origen,carta);
      strcat(destino,carta);
      mover_archivo(origen,destino);
      cont_cartas++;
      cont_tamanio++;
    }
    cont_cartas = 0;
    while (cont_cartas < 7){
      carta = escoger_carta_random(107-cont_tamanio);
      char origen[50] = "Mazo/";
      char destino[50] = "Jugador4/";
      strcat(origen,carta);
      strcat(destino,carta);
      mover_archivo(origen,destino);
      cont_cartas++;
      cont_tamanio++;
    }
}

//Funcion utilizada para que el jugador juegue una carta de su mano y esta se mueva al directorio Juego
void tirar_carta(int carta_a_jugar, char* origen){
  char* carta = (char*)malloc(sizeof(char)*30);
  carta_a_jugar--;
  carta = encontrar_carta("Jugador1", carta_a_jugar);
  char destino[50] = "Juego/";
  strcat(origen,carta);
  strcat(destino,carta);
  mover_archivo(origen,destino);
}

//Funcion que elimina la carta dado su nombre y el directorio en que se encuentra
void eliminar_carta(char* origen, int carta_a_jugar){
  char* carta = (char*)malloc(sizeof(char)*30);
  carta_a_jugar--;
  carta = encontrar_carta("Jugador2", carta_a_jugar);
  strcat(origen,carta);
  remove(origen);
}

int main(){
  ///Creacion de directorios y de las cartas///////////
  crear_directorios();
  crear_numeros1_9();
  crear_0();
  crear_especiales();
  //Se reparten 7 cartas a cada jugador
  repartir_cartas();
  return 0;
}
